#include "MiServer.hpp"
#include <iostream>
#include <MiRak/RakNetworkFactory.h>
#include <MiRak/PacketEnumerations.h>
#include <MiRak/RakEncr.h>
#include "server/Server.hpp"
#include "server/ServerInstance.hpp"
#include "event/EventPool.hpp"
#include "player/PlayerTypes.hpp"
#include "packet/PlayerSync.hpp"
#include "packet/AimSync.hpp"
#include "packet/BulletSync.hpp"
#include "packet/PassengerSync.hpp"
#include "packet/UnoccupiedSync.hpp"
#include "packet/VehicleSync.hpp"
#include "vehicle/VehiclePool.hpp"
#include "RPC/RPC.hpp"

mimp::ServerInfo::ServerInfo(const char* hostname, const char* gamemode, const char* lang, const unsigned int max_players) :
	hostname(hostname), gamemode(gamemode), lang(lang), max_players(max_players)
{
}

mimp::Server::Server(const ServerInfo& info): m_info(info)
{
	this->m_RakServer = nullptr;
	this->m_initialized = false;
	this->m_port = 0;

	this->m_playerPool = new internal::player::PlayerPool(info.max_players);
	this->m_vehiclePool = new internal::vehicle::VehiclePool(MAX_VEHICLES);
	this->m_eventPool = new internal::event::EventPool();

}

int mimp::Server::Init(uint16_t port) {
	if (internal::server::GetServerInstance() != nullptr) {
		return -1;
	}


	this->m_RakServer = RakNetworkFactory::GetRakServerInterface();
	this->m_port = port;

	srand((unsigned int)time(NULL));
	RakNet::RakEncr::m_srvChallenge = (unsigned int)rand();
	RakNet::RakEncr::setPort(port);

	this->m_RakServer->Start(this->m_info.max_players, 0, 5, port);
	this->m_RakServer->StartOccasionalPing();

	internal::server::SetServerInstance(this);
	internal::RPC::RegisterServerRPCs(this->m_RakServer);

	if (this->m_vehiclePool->IsValidVehicle(100)) {
		return 0;
	}

	this->m_eventPool->Emit(internal::event::SERVER_EVENT_SERVERINIT, nullptr);

	return 1;
}

int mimp::Server::ServerTick(void) {
	unsigned char packetIdentifier;
	Packet* pkt = nullptr;
	
	while (pkt = this->m_RakServer->Receive()) {
		
		if ((unsigned char)pkt->data[0] == ID_TIMESTAMP)
		{
			if (pkt->length > sizeof(unsigned char) + sizeof(unsigned int)) {
				
				packetIdentifier = (unsigned char)pkt->data[sizeof(unsigned char) + sizeof(unsigned int)];
				std::cout << "new Packet ID: " << packetIdentifier << '\n';
			}
			else {
				std::cout << "Discard packet\n";
				return 1;
			}
				
		}
		else
			packetIdentifier = (unsigned char)pkt->data[0];

		PLAYERID playerID = pkt->playerIndex;
		switch (packetIdentifier) {
		case ID_DISCONNECTION_NOTIFICATION: {
			this->m_playerPool->Remove(playerID);
			break;
		}
		case ID_NEW_INCOMING_CONNECTION: {
			break;
		}
		case ID_CONNECTION_LOST: {
			this->m_playerPool->Remove(playerID);
			break;
		}
		case ID_PLAYER_SYNC: {
			mimp::internal::packet::PlayerSync(pkt);
			break;
		}
		case ID_AIM_SYNC: {
			mimp::internal::packet::AimSync(pkt);
			break;
		}
		case ID_BULLET_SYNC: {
			mimp::internal::packet::BulletSync(pkt);
			break;
		}
		case ID_VEHICLE_SYNC: {
			mimp::internal::packet::VehicleSync(pkt);
			break;
		}
		case ID_UNOCCUPIED_SYNC: {
			mimp::internal::packet::UnoccupiedSync(pkt);
			break;
		}
		}
		this->m_RakServer->DeallocatePacket(pkt);
	}
	return 1;
}