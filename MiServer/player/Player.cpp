#include "player/Player.hpp"


mimp::Player::Player(PlayerID rakPlayerID, PLAYERID playerID, const char* nickname)
    : m_rakPlayerId(rakPlayerID), m_playerId(playerID), m_nickName(nickname),
    m_OnFootSyncData(new internal::packet::ONFOOT_SYNC_DATA{}),
    m_InCarSyncData(new internal::packet::INCAR_SYNC_DATA{}),
    m_BulletData(new internal::packet::BULLET_SYNC_DATA{}),
    m_PassengerData(new internal::packet::PASSENGER_SYNC_DATA{}),
    m_UnoccupiedData(new internal::packet::UNOCCUPIED_SYNC_DATA{}),
    m_clientPort(0), m_score(0), m_ping(0), m_currentVehicleId(0),
    m_skin(0), m_rotation(0.0f), m_color(0), m_fightingStyle(0),
    m_checkpointActive(false), m_checkpointSize(0.0f),
    m_playerInCheckpoint(false), m_interiorId(0) 
{
    std::memset(m_spawn, 0, sizeof(m_spawn));
    std::memset(m_checkpointPos, 0, sizeof(m_checkpointPos));
}

