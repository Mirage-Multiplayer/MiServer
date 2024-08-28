#include <MiServer/player/Player.hpp>
#include <MiServer/RPC/RPCList.hpp>
#include <cstring>

mimp::Player::Player(PlayerID rakPlayerID, PLAYERID playerID, const char *nickname)
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

void mimp::Player::setSkin(const int skinid)
{
    int skin = 0;
    if (skinid == -1)
    {
        // rd
    }
    else
    {
        skin = skinid;
    }

    this->m_skin = skin;
    mimp::internal::RPC::outgoing::Handler::SetPlayerSkin(this->m_playerId, skinid);
}

void mimp::Player::setHealth(const float value)
{
    mimp::internal::RPC::outgoing::Handler::SetPlayerHealth(this->m_playerId, value);
}

void mimp::Player::setArmour(const float value)
{
    mimp::internal::RPC::outgoing::Handler::SetPlayerArmour(this->m_playerId, value);
}
void mimp::Player::setSpawn(const float x, const float y, const float z)
{
    this->m_spawn[0] = x;
    this->m_spawn[1] = y;
    this->m_spawn[2] = z;
}
void mimp::Player::setPos(const float x, const float y, const float z)
{
    mimp::internal::RPC::outgoing::Handler::SetPlayerPos(this->m_playerId, x, y, z);
}
void mimp::Player::setRotation(const float r)
{
    mimp::internal::RPC::outgoing::Handler::SetPlayerFacingAngle(this->m_playerId, r);
}
void mimp::Player::setColor(const int color)
{
    mimp::internal::RPC::outgoing::Handler::SetPlayerColor(this->m_playerId, color);
}

void mimp::Player::clientMessage(const int color, const char *message)
{
    mimp::internal::RPC::outgoing::Handler::SendClientMessage(this->m_playerId, color, strlen(message), message);
}
