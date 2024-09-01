#include <MiServer/MiServer.hpp>
#include <iostream>
#include <MiRak/RakNetworkFactory.h>
#include <MiRak/PacketEnumerations.h>
#include <MiRak/RakEncr.h>
#include <MiServer/server/Server.hpp>
#include <MiServer/server/ServerInstance.hpp>
#include <MiServer/event/EventPool.hpp>
#include <MiServer/packet/PlayerSync.hpp>
#include <MiServer/packet/AimSync.hpp>
#include <MiServer/packet/BulletSync.hpp>
#include <MiServer/packet/PassengerSync.hpp>
#include <MiServer/packet/UnoccupiedSync.hpp>
#include <MiServer/packet/VehicleSync.hpp>
#include <MiServer/netgame/NetGame.hpp>
#include <MiServer/RPC/RPC.hpp>
#include <MiServer/config.h>

mimp::ServerInfo::ServerInfo(const char *hostname, const char *gamemode, const char *lang, const unsigned int max_players) : hostname(hostname), gamemode(gamemode), lang(lang), max_players(max_players)
{
}

mimp::Server::Server(const ServerInfo &info) : m_info(info),
											   m_port(0),
											   m_initialized(false)
{
	this->m_pNetGame = new mimp::CNetGame(info.max_players, 6000);
	this->m_pEventPool = new internal::event::EventPool();
	this->m_pRakServer = RakNetworkFactory::GetRakServerInterface();
}

mimp::Server::Server(const ServerInfo &info, const ServerConfig &config) : m_info(info),
																		   m_port(0),
																		   m_initialized(false),
																		   m_cfg(config)
{
	this->m_pNetGame = new mimp::CNetGame(info.max_players, 6000);
	this->m_pEventPool = new internal::event::EventPool();
	this->m_pRakServer = RakNetworkFactory::GetRakServerInterface();
}

mimp::Server::~Server()
{
	delete this->m_pNetGame;
	delete this->m_pRakServer;
	delete this->m_pEventPool;
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

	this->m_pRakServer->Start(this->m_info.max_players, 0, 5, port);
	this->m_pRakServer->StartOccasionalPing();

	internal::server::SetServerInstance(this);
	internal::RPC::RegisterServerRPCs(this->m_pRakServer);

	this->m_initialized = true;
	std::cout << "[Mi:MP] Successfully initialized Mi:MP ' Mi-Server " << MISERVER_VERSION << " ' \n";
	this->m_pEventPool->Emit(internal::event::SERVER_EVENT_SERVERINIT, nullptr);
	return 1;
}

int mimp::Server::Shutdown(void)
{
	this->m_pRakServer->Disconnect(300);
	RakNetworkFactory::DestroyRakServerInterface(this->m_pRakServer);

	delete this->m_pNetGame;
	delete this->m_pRakServer;
	delete this->m_pEventPool;

	this->m_pNetGame = new mimp::CNetGame(this->m_info.max_players, 6000);
	this->m_pEventPool = new internal::event::EventPool();

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
	while ((pkt = this->m_pRakServer->Receive()))
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

		WORD playerID = pkt->playerIndex;
		switch (packetIdentifier)
		{
		case ID_DISCONNECTION_NOTIFICATION:
		{
			this->m_pNetGame->GetPlayerPool()->DeleteAt(playerID);
			break;
		}
		case ID_NEW_INCOMING_CONNECTION:
		{
			break;
		}
		case ID_CONNECTION_LOST:
		{
			this->m_pNetGame->GetPlayerPool()->DeleteAt(playerID);
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
		this->m_pRakServer->DeallocatePacket(pkt);
	}
	return 1;
}