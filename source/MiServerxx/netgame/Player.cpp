#include <MiServerxx/netgame/Player.hpp>
#include <MiServerxx/RPC/RPCList.hpp>
#include <cstring>

mimp::CPlayer::CPlayer(PlayerID rakPlayerID, WORD playerID, const char *nickname)
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

void mimp::CPlayer::setSkin(const int skinid)
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

void mimp::CPlayer::setHealth(const float value)
{
    mimp::internal::RPC::outgoing::Handler::SetPlayerHealth(this->m_playerId, value);
}

void mimp::CPlayer::setArmour(const float value)
{
    mimp::internal::RPC::outgoing::Handler::SetPlayerArmour(this->m_playerId, value);
}
void mimp::CPlayer::setSpawn(const float x, const float y, const float z)
{
    this->m_spawn[0] = x;
    this->m_spawn[1] = y;
    this->m_spawn[2] = z;
}
void mimp::CPlayer::setPos(const float x, const float y, const float z)
{
    mimp::internal::RPC::outgoing::Handler::SetPlayerPos(this->m_playerId, x, y, z);
}
void mimp::CPlayer::setRotation(const float r)
{
    mimp::internal::RPC::outgoing::Handler::SetPlayerFacingAngle(this->m_playerId, r);
}
void mimp::CPlayer::setColor(const int color)
{
    mimp::internal::RPC::outgoing::Handler::SetPlayerColor(this->m_playerId, color);
}

void mimp::CPlayer::clientMessage(const int color, const char *message)
{
    mimp::internal::RPC::outgoing::Handler::SendClientMessage(this->m_playerId, color, strlen(message), message);
}

void mimp::CPlayer::setPlayerCheckpoint(const float x, const float y, const float z, const float size)
{
    this->m_checkpointPos[0] = x;
    this->m_checkpointPos[1] = y;
    this->m_checkpointPos[2] = z;
    this->m_checkpointSize = size;
    this->m_checkpointActive = true;
    mimp::internal::RPC::outgoing::Handler::SetCheckpoint(this->m_playerId, x, y, z, size);
}

void mimp::CPlayer::disableCheckpoint(void)
{
    this->m_checkpointActive = false;
    this->m_checkpointPos[0] = 0.0f;
    this->m_checkpointPos[1] = 0.0f;
    this->m_checkpointPos[2] = 0.0f;
    this->m_checkpointSize = 0.0f;
    mimp::internal::RPC::outgoing::Handler::DisableCheckpoint(this->m_playerId);
}