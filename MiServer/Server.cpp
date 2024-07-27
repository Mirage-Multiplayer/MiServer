#include "MiServer.hpp"
#include <iostream>
#include <MiRak/RakNetworkFactory.h>
#include <MiRak/PacketEnumerations.h>
#include "Server.hpp"
#include "event/EventPool.hpp"
#include "player/PlayerTypes.hpp"
#include "packet/PlayerSync.hpp"
#include "packet/AimSync.hpp"
#include "packet/BulletSync.hpp"
#include "packet/PassengerSync.hpp"
#include "packet/UnoccupiedSync.hpp"
#include "packet/VehicleSync.hpp"


mimp::ServerInfo::ServerInfo(const char* hostname, const char* gamemode, const char* lang, const unsigned int max_players) :
	hostname(hostname), gamemode(gamemode), lang(lang), max_players(max_players)
{
}

mimp::Server::Server(const ServerInfo& info): m_info(info), m_playerPool(info.max_players)
{
	this->m_RakServer = nullptr;
	this->m_initialized = false;
	this->m_port = 0;
}

int mimp::Server::Init(uint16_t port) {
	this->m_RakServer = RakNetworkFactory::GetRakServerInterface();
	this->m_port = port;
	this->m_RakServer->Start(this->m_info.max_players, 0, 5, port);
	this->m_RakServer->StartOccasionalPing();
	this->m_eventPool.Emit(internal::event::SERVER_EVENT_SERVERINIT, 0);
	return 1;
}

int mimp::Server::ServerTick(void) {
	unsigned char packetIdentifier;
	Packet* pkt = nullptr;
	
	while (pkt = this->m_RakServer->Receive()) {
		std::cout << "Receiving packet\n";
		if ((unsigned char)pkt->data[0] == ID_TIMESTAMP)
		{
			if (pkt->length > sizeof(unsigned char) + sizeof(unsigned int))
				packetIdentifier = (unsigned char)pkt->data[sizeof(unsigned char) + sizeof(unsigned int)];
			else
				return 1;
		}
		else
			packetIdentifier = (unsigned char)pkt->data[0];

		PLAYERID playerID = pkt->playerIndex;
		switch (packetIdentifier) {
		case ID_DISCONNECTION_NOTIFICATION: {
			this->m_playerPool.Remove(playerID);
			break;
		}
		case ID_CONNECTION_LOST: {
			this->m_playerPool.Remove(playerID);
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