#pragma once
#include <MiServerxx/core/Core.hpp>
#include <MiRak/PacketEnumerations.h>

void mimp::CCore::addPacketHandler(const int uid, std::function<void(const int, Packet*)> fn) {
	this->m_Packets[uid].push_back(fn);
}

bool mimp::CCore::hasPacketHandler(const int uid) {
	return (this->m_Packets.find(uid) != this->m_Packets.end());
}

void mimp::CCore::HandlePacket(const int uid, Packet* packet) {
	for (const auto& fn : this->m_Packets[uid]) {
		fn(uid, packet);
	}
}

#define LOAD_PACKET(uid, name) \
	extern void Packet_##name(const int, Packet* packet); \
	this->addPacketHandler(uid, Packet_##name);

void mimp::CCore::LoadPackets(void) {
	LOAD_PACKET(ID_DISCONNECTION_NOTIFICATION, DisconnectionNotification)
	LOAD_PACKET(ID_NEW_INCOMING_CONNECTION, NewIncomingConnection)
	LOAD_PACKET(ID_CONNECTION_LOST, ConnectionLost)
	LOAD_PACKET(ID_VEHICLE_SYNC, VehicleSync)
	LOAD_PACKET(ID_UNOCCUPIED_SYNC, UnoccupiedSync)
	LOAD_PACKET(ID_PLAYER_SYNC, PlayerSync)
	LOAD_PACKET(ID_AIM_SYNC, AimSync)
	LOAD_PACKET(ID_BULLET_SYNC, BulletSync)
}
