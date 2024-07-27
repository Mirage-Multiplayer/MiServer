#ifndef __MISERVER_PLAYER_HPP
#define __MISERVER_PLAYER_HPP
#include <string>
#include "types.h"
#include <MiRak/NetworkTypes.h>
#include "packet/PlayerSync.hpp"
#include "packet/AimSync.hpp"
#include "packet/BulletSync.hpp"
#include "packet/VehicleSync.hpp"
#include "packet/UnoccupiedSync.hpp"
#include "packet/SyncData.hpp"
#include "packet/PassengerSync.hpp"
#include "packet/PositionSync.hpp"
#include "PlayerTypes.hpp"
#include <iostream>

namespace mimp {
	class Player {
	public:
		Player(PlayerID rakPlayerID, PLAYERID playerID, const char* nickname);

		inline const PLAYERID getPlayerId(void) const {
			return this->m_playerId;
		}

		inline const PlayerID getRakPlayerId(void) const {
			return this->m_rakPlayerId;
		}

		inline const std::string getNickName(void) const {
			return this->m_nickName;
		}

		inline void setIP(const char* ip) {
			this->m_IP = ip;
		}

		inline const std::string getIP(void) const {
			return this->m_IP;
		}

		inline void setClientPort(const uint16_t port) {
			this->m_clientPort = port;
		}

		inline const uint16_t getClientPort(void) const {
			return this->m_clientPort;
		}

		inline void setScore(const int score) {
			this->m_score = score;
		}

		inline const int getScore(void) const {
			return this->m_score;
		}

		inline void setPing(const DWORD ping) {
			this->m_ping = ping;
		}

		inline const DWORD getPing(void) const {
			return this->m_ping;
		}

		inline void setCurrentVehicle(const WORD cvid) {
			this->m_currentVehicleId = cvid;
		}

		inline const WORD getCurrentVehicle(void) const {
			return this->m_currentVehicleId;
		}

		inline void setSkin(const int skin) {
			this->m_skin = skin;
		}

		inline const int getSkin(void) const {
			return this->m_skin;
		}

		inline void setSpawn(float x, float y, float z) {
			this->m_spawn[0] = x;
			this->m_spawn[1] = y;
			this->m_spawn[2] = z;
		}

		inline void getSpawn(float& x, float& y, float& z) const {
			x = this->m_spawn[0];
			y = this->m_spawn[1];
			z = this->m_spawn[2];
		}

		inline void setRotation(const float rotation) {
			this->m_rotation = rotation;
		}

		inline const float getRotation(void) const {
			return this->m_rotation;
		}

		inline void setColor(const DWORD color) {
			this->m_color = color;
		}

		inline const DWORD getColor(void) const {
			return this->m_color;
		}

		inline void setFightingStyle(const BYTE style) {
			this->m_fightingStyle = style;
		}

		inline const BYTE getFightingStyle(void) const {
			return this->m_fightingStyle;
		}

		inline void setCheckpointActive(const bool active) {
			this->m_checkpointActive = active;
		}

		inline const bool getCheckpointActive(void) const {
			return this->m_checkpointActive;
		}

		inline void setCheckpointPos(float x, float y, float z) {
			this->m_checkpointPos[0] = x;
			this->m_checkpointPos[1] = y;
			this->m_checkpointPos[2] = z;
		}

		inline void getCheckpointPos(float& x, float& y, float& z) const {
			x = this->m_checkpointPos[0];
			y = this->m_checkpointPos[1];
			z = this->m_checkpointPos[2];
		}

		inline void setCheckpointSize(const float size) {
			this->m_checkpointSize = size;
		}

		inline const float getCheckpointSize(void) const {
			return this->m_checkpointSize;
		}

		inline void setPlayerInCheckpoint(const bool inCheckpoint) {
			this->m_playerInCheckpoint = inCheckpoint;
		}

		inline const bool getPlayerInCheckpoint(void) const {
			return this->m_playerInCheckpoint;
		}

		inline void setInteriorId(const int i) {
			this->m_interiorId = i;
		}



		inline internal::packet::ONFOOT_SYNC_DATA* getOnFootSyncData() const {
			return this->m_OnFootSyncData;
		}

		inline internal::packet::INCAR_SYNC_DATA* getInCarSyncData() const {
			return this->m_InCarSyncData;
		}

	private:

		friend void internal::packet::PlayerSync(Packet* pkt);
		friend void internal::packet::AimSync(Packet* pkt);
		friend void internal::packet::VehicleSync(Packet* pkt);
		friend void internal::packet::BulletSync(Packet* pkt);
		friend void internal::packet::PassengerSync(Packet* pkt);
		friend void internal::packet::UnoccupiedSync(Packet* pkt);
		friend void internal::packet::UpdatePosition(int iPlayerID, float fX, float fY, float fZ);

		internal::packet::ONFOOT_SYNC_DATA* m_OnFootSyncData;
		internal::packet::INCAR_SYNC_DATA* m_InCarSyncData;
		internal::packet::BULLET_SYNC_DATA* m_BulletData;
		internal::packet::PASSENGER_SYNC_DATA* m_PassengerData;
		internal::packet::UNOCCUPIED_SYNC_DATA* m_UnoccupiedData;

		PLAYERID m_playerId;
		PlayerID m_rakPlayerId;
		std::string m_nickName;

		std::string m_IP;
		uint16_t m_clientPort;

		int m_score;
		DWORD m_ping;

		WORD m_currentVehicleId;
		int m_skin;
		float m_spawn[3];
		float m_rotation;
		DWORD m_color;
		BYTE m_fightingStyle;

		bool m_checkpointActive;
		float m_checkpointPos[3];
		float m_checkpointSize;
		bool m_playerInCheckpoint;

		int m_interiorId;




	};
}
#endif