#include <MiServer/MiServer.hpp>
#include <iostream>
#include <MiRak/RakNetworkFactory.h>
#include <MiRak/PacketEnumerations.h>
#include <MiRak/RakEncr.h>
#include <MiServer/server/Server.hpp>
#include <MiServer/server/ServerInstance.hpp>
#include <MiServer/event/EventPool.hpp>
#include <MiServer/player/PlayerTypes.hpp>
#include <MiServer/packet/PlayerSync.hpp>
#include <MiServer/packet/AimSync.hpp>
#include <MiServer/packet/BulletSync.hpp>
#include <MiServer/packet/PassengerSync.hpp>
#include <MiServer/packet/UnoccupiedSync.hpp>
#include <MiServer/packet/VehicleSync.hpp>
#include <MiServer/vehicle/VehiclePool.hpp>
#include <MiServer/RPC/RPC.hpp>
#include <MiServer/config.h>

mimp::ServerInfo::ServerInfo(const char *hostname, const char *gamemode, const char *lang, const unsigned int max_players) : hostname(hostname), gamemode(gamemode), lang(lang), max_players(max_players)
{
}

mimp::Server::Server(const ServerInfo &info) : m_info(info),
											   m_port(0),
											   m_initialized(false)
{
	this->m_playerPool = new internal::player::PlayerPool(this->m_info.max_players);
	this->m_vehiclePool = new internal::vehicle::VehiclePool(MAX_VEHICLES);
	this->m_eventPool = new internal::event::EventPool();
	this->m_RakServer = RakNetworkFactory::GetRakServerInterface();
}

mimp::Server::Server(const ServerInfo &info, const ServerConfig &config) : m_info(info),
																		   m_port(0),
																		   m_initialized(false),
																		   m_cfg(config)
{
	this->m_playerPool = new internal::player::PlayerPool(this->m_info.max_players);
	this->m_vehiclePool = new internal::vehicle::VehiclePool(MAX_VEHICLES);
	this->m_eventPool = new internal::event::EventPool();
	this->m_RakServer = RakNetworkFactory::GetRakServerInterface();
}

mimp::Server::~Server()
{
	delete this->m_RakServer;
	delete this->m_playerPool;
	delete this->m_vehiclePool;
	delete this->m_eventPool;
}

int mimp::Server::Init(uint16_t port)
{

	std::cout << "[Mi:MP] Initializing Mi:MP Server instance version " << MISERVER_VERSION << "\n";

	if (internal::server::GetServerInstance() != nullptr)
	{
		std::cout << "[Mi:MP] Server instance already Loaded!. Aborting...";
		return -1;
	}
	this->m_port = port;

	srand((unsigned int)time(NULL));
	RakNet::RakEncr::m_srvChallenge = (unsigned int)rand();
	RakNet::RakEncr::setPort(port);

	this->m_RakServer->Start(this->m_info.max_players, 0, 5, port);
	this->m_RakServer->StartOccasionalPing();

	internal::server::SetServerInstance(this);
	internal::RPC::RegisterServerRPCs(this->m_RakServer);

	this->m_initialized = true;
	std::cout << "[Mi:MP] Successfully initialized Mi:MP ' Mi-Server " << MISERVER_VERSION << " ' \n";
	this->m_eventPool->Emit(internal::event::SERVER_EVENT_SERVERINIT, nullptr);
	return 1;
}

int mimp::Server::Shutdown(void)
{
	this->m_RakServer->Disconnect(300);
	RakNetworkFactory::DestroyRakServerInterface(this->m_RakServer);

	delete this->m_playerPool;
	delete this->m_vehiclePool;
	delete this->m_eventPool;

	this->m_playerPool = new internal::player::PlayerPool(this->m_info.max_players);
	this->m_vehiclePool = new internal::vehicle::VehiclePool(MAX_VEHICLES);
	this->m_eventPool = new internal::event::EventPool();

	this->m_port = 0;

	RakNet::RakEncr::m_srvChallenge = 0;
	RakNet::RakEncr::setPort(0);

	internal::server::SetServerInstance(nullptr);
	return 1;
}

int mimp::Server::ServerTick(void)
{
	unsigned char packetIdentifier;
	Packet *pkt = nullptr;
	while ((pkt = this->m_RakServer->Receive()))
	{
		if ((unsigned char)pkt->data[0] == ID_TIMESTAMP)
		{
			if (pkt->length > sizeof(unsigned char) + sizeof(unsigned int))
			{

				packetIdentifier = (unsigned char)pkt->data[sizeof(unsigned char) + sizeof(unsigned int)];
			}
			else
			{
				return 1;
			}
		}
		else
			packetIdentifier = (unsigned char)pkt->data[0];

		PLAYERID playerID = pkt->playerIndex;
		switch (packetIdentifier)
		{
		case ID_DISCONNECTION_NOTIFICATION:
		{
			this->m_playerPool->Remove(playerID);
			break;
		}
		case ID_NEW_INCOMING_CONNECTION:
		{
			break;
		}
		case ID_CONNECTION_LOST:
		{
			this->m_playerPool->Remove(playerID);
			break;
		}
		case ID_PLAYER_SYNC:
		{
			mimp::internal::packet::PlayerSync(pkt);
			break;
		}
		case ID_AIM_SYNC:
		{
			mimp::internal::packet::AimSync(pkt);
			break;
		}
		case ID_BULLET_SYNC:
		{
			mimp::internal::packet::BulletSync(pkt);
			break;
		}
		case ID_VEHICLE_SYNC:
		{
			mimp::internal::packet::VehicleSync(pkt);
			break;
		}
		case ID_UNOCCUPIED_SYNC:
		{
			mimp::internal::packet::UnoccupiedSync(pkt);
			break;
		}
		}
		this->m_RakServer->DeallocatePacket(pkt);
	}
	return 1;
}