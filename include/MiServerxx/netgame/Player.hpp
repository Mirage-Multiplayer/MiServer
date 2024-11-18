#pragma once
#include <string>
#include <MiServerxx/types.h>
#include <MiRak/NetworkTypes.h>
#include <MiServerxx/RPC/RPCList.hpp>
#include <MiServerxx/packet/PlayerSync.hpp>
#include <MiServerxx/packet/AimSync.hpp>
#include <MiServerxx/packet/BulletSync.hpp>
#include <MiServerxx/packet/VehicleSync.hpp>
#include <MiServerxx/packet/UnoccupiedSync.hpp>
#include <MiServerxx/packet/SyncData.hpp>
#include <MiServerxx/packet/PassengerSync.hpp>
#include <MiServerxx/packet/PositionSync.hpp>
#include <iostream>

namespace mimp
{
	/**
	 * Player object.
	 */
	class CPlayer
	{
	public:
		CPlayer(PlayerID rakPlayerID, WORD playerID, const char *nickname);

		/**
		 * Get the player's ID.
		 * @return The player's index in PlayerPool.
		 */
		inline const WORD getPlayerId(void) const
		{
			return this->m_playerId;
		}

		/**
		 * Get the RakNet PlayerID.
		 * @return The RakNet player's PlayerID.
		 */
		inline const PlayerID getRakPlayerId(void) const
		{
			return this->m_rakPlayerId;
		}

		/**
		 * Get the player's nickname.
		 * @return The player's nickname.
		 */
		inline const std::string getNickName(void) const
		{
			return this->m_nickName;
		}

		inline const float getHealth(void) const
		{
			return this->m_OnFootSyncData->byteHealth;
		}

		inline const float getArmour(void) const
		{
			return this->m_OnFootSyncData->byteArmour;
		}

		inline const int getInteriorId(void) const
		{
			return this->m_interiorId;
		}

		/**
		 * Get the player's IP address.
		 * @return The player's IP address as a string.
		 */
		inline const std::string getIP(void) const
		{
			return this->m_IP;
		}

		/**
		 * Get the client's port number.
		 * @return The client's port number.
		 */
		inline const uint16_t getClientPort(void) const
		{
			return this->m_clientPort;
		}

		/**
		 * Get the player's score.
		 * @return The player's score as an integer.
		 */
		inline const int getScore(void) const
		{
			return this->m_score;
		}

		/**
		 * Get the player's ping.
		 * @return The player's ping in milliseconds.
		 */
		inline const DWORD getPing(void) const
		{
			return this->m_ping;
		}

		/**
		 * Get the ID of the vehicle the player is currently in.
		 * @return The current vehicle ID.
		 */
		inline const WORD getCurrentVehicle(void) const
		{
			return this->m_currentVehicleId;
		}

		/**
		 * Get the player's skin ID.
		 * @return The player's skin ID as an integer.
		 */
		inline const int getSkin(void) const
		{
			return this->m_skin;
		}

		/**
		 * Get the player's spawn position.
		 * @param[out] x The x-coordinate of the spawn position.
		 * @param[out] y The y-coordinate of the spawn position.
		 * @param[out] z The z-coordinate of the spawn position.
		 */
		inline void getSpawn(float &x, float &y, float &z) const
		{
			x = this->m_spawn[0];
			y = this->m_spawn[1];
			z = this->m_spawn[2];
		}

		inline void getPos(float &x, float &y, float &z) const
		{
			x = this->m_OnFootSyncData->vecPos[0];
			y = this->m_OnFootSyncData->vecPos[1];
			z = this->m_OnFootSyncData->vecPos[2];
		}

		/**
		 * Get the player's rotation.
		 * @return The player's rotation in degrees.
		 */
		inline const float getRotation(void) const
		{
			return this->m_rotation;
		}

		/**
		 * Get the player's color.
		 * @return The player's color as a DWORD value.
		 */
		inline const DWORD getColor(void) const
		{
			return this->m_color;
		}

		/**
		 * Get the player's fighting style.
		 * @return The player's fighting style as a BYTE value.
		 */
		inline const BYTE getFightingStyle(void) const
		{
			return this->m_fightingStyle;
		}

		/**
		 * Check if the player has an active checkpoint.
		 * @return True if the player has an active checkpoint, false otherwise.
		 */
		inline const bool getCheckpointActive(void) const
		{
			return this->m_checkpointActive;
		}

		/**
		 * Get the position of the player's checkpoint.
		 * @param[out] x The x-coordinate of the checkpoint position.
		 * @param[out] y The y-coordinate of the checkpoint position.
		 * @param[out] z The z-coordinate of the checkpoint position.
		 */
		inline void getCheckpointPos(float &x, float &y, float &z) const
		{
			x = this->m_checkpointPos[0];
			y = this->m_checkpointPos[1];
			z = this->m_checkpointPos[2];
		}

		/**
		 * Get the size of the player's checkpoint.
		 * @return The checkpoint size as a float.
		 */
		inline const float getCheckpointSize(void) const
		{
			return this->m_checkpointSize;
		}

		/**
		 * Check if the player is in a checkpoint.
		 * @return True if the player is in a checkpoint, false otherwise.
		 */
		inline const bool isPlayerInCheckpoint(void) const
		{
			return this->m_playerInCheckpoint;
		}

		void setHealth(const float value);
		void setArmour(const float value);
		void setSkin(const int skinid);
		void setSpawn(const float x, const float y, const float z);
		void setPos(const float x, const float y, const float z);
		void setRotation(const float r);
		void setColor(const int color);
		void clientMessage(const int color, const char *message);
		void setPlayerCheckpoint(const float x, const float y, const float z, const float size);
		void disableCheckpoint(void);
		void chatBubble(const uint16_t playerid, const uint32_t color, const float drawDistance, const uint32_t expiretime, uint8_t textLength, char* text);

		/**
		 * Get the player's on-foot synchronization data.
		 * @return A pointer to the player's ONFOOT_SYNC_DATA structure.
		 */
		inline internal::packet::ONFOOT_SYNC_DATA *getOnFootSyncData()
		{
			return this->m_OnFootSyncData;
		}

		/**
		 * Get the player's in-car synchronization data.
		 * @return A pointer to the player's INCAR_SYNC_DATA structure.
		 */
		inline internal::packet::INCAR_SYNC_DATA *getInCarSyncData()
		{
			return this->m_InCarSyncData;
		}

		inline internal::packet::BULLET_SYNC_DATA* getBulletData()
		{
			return this->m_BulletData;
		}

		inline internal::packet::PASSENGER_SYNC_DATA* getPassengerData()
		{
			return this->m_PassengerData;
		}

		inline internal::packet::UNOCCUPIED_SYNC_DATA* getUnoccupiedData() {
			return this->m_UnoccupiedData;
		}

	public:
		inline void _setIP(const char *ip)
		{
			this->m_IP = ip;
		}

		inline void _setClientPort(const uint16_t port)
		{
			this->m_clientPort = port;
		}

		inline void _setScore(const int score)
		{
			this->m_score = score;
		}

		inline void _setPing(const DWORD ping)
		{
			this->m_ping = ping;
		}

		inline void _setCurrentVehicle(const WORD cvid)
		{
			this->m_currentVehicleId = cvid;
		}

		inline void _setSkin(const int skin)
		{
			this->m_skin = skin;
		}

		inline void _setSpawn(float x, float y, float z)
		{
			this->m_spawn[0] = x;
			this->m_spawn[1] = y;
			this->m_spawn[2] = z;
		}

		inline void _setColor(const DWORD color)
		{
			this->m_color = color;
		}

		inline void _setRotation(const float rotation)
		{
			this->m_rotation = rotation;
		}

		inline void _setFightingStyle(const BYTE style)
		{
			this->m_fightingStyle = style;
		}

		inline void _setCheckpointActive(const bool active)
		{
			this->m_checkpointActive = active;
		}

		inline void _setCheckpointPos(float x, float y, float z)
		{
			this->m_checkpointPos[0] = x;
			this->m_checkpointPos[1] = y;
			this->m_checkpointPos[2] = z;
		}

		inline void _setCheckpointSize(const float size)
		{
			this->m_checkpointSize = size;
		}

		inline void _setPlayerInCheckpoint(const bool inCheckpoint)
		{
			this->m_playerInCheckpoint = inCheckpoint;
		}

		inline void _setInteriorId(const int i)
		{
			this->m_interiorId = i;
		}

	private:
		internal::packet::ONFOOT_SYNC_DATA *m_OnFootSyncData;
		internal::packet::INCAR_SYNC_DATA *m_InCarSyncData;
		internal::packet::BULLET_SYNC_DATA *m_BulletData;
		internal::packet::PASSENGER_SYNC_DATA *m_PassengerData;
		internal::packet::UNOCCUPIED_SYNC_DATA *m_UnoccupiedData;

		WORD m_playerId;
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