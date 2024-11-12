#include <MiServerxx/netgame/Player.hpp>
#include <MiServerxx/RPC/RPCList.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <cstring>

using namespace mimp::internal::server;
using namespace mimp::internal::RPC;

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

    mimp::internal::RPC::ORPCSetPlayerSkin rpc;
    rpc.wPlayerID = this->m_playerId;
    rpc.dSkinID = skinid;
    GetCoreInstance()->BroadcastRPC(&rpc);
}

void mimp::CPlayer::setHealth(const float value)
{
    ORPCSetPlayerHealth rpc;
    rpc.health = value;
    GetCoreInstance()->SendRPC(this->m_playerId, &rpc);
}

void mimp::CPlayer::setArmour(const float value)
{
    ORPCSetPlayerArmour rpc;
    rpc.armour = value;
    GetCoreInstance()->SendRPC(this->m_playerId, &rpc);
}
void mimp::CPlayer::setSpawn(const float x, const float y, const float z)
{
    this->m_spawn[0] = x;
    this->m_spawn[1] = y;
    this->m_spawn[2] = z;
}
void mimp::CPlayer::setPos(const float x, const float y, const float z)
{
    ORPCSetPlayerPos rpc;
    rpc.x = x;
    rpc.y = y;
    rpc.z = z;
    GetCoreInstance()->SendRPC(this->m_playerId, &rpc);
}
void mimp::CPlayer::setRotation(const float r)
{
    ORPCSetPlayerFacingAngle rpc;
    rpc.angle = r;
    GetCoreInstance()->SendRPC(this->m_playerId, &rpc);
}
void mimp::CPlayer::setColor(const int color)
{
    ORPCSetPlayerColor rpc;
    rpc.wPlayerID = this->m_playerId;
    rpc.dColor = color;
    GetCoreInstance()->BroadcastRPC(&rpc);
}

void mimp::CPlayer::clientMessage(const int color, const char *message)
{
    ORPCSendClientMessage rpc;
    rpc.dColor = color;
    rpc.dMessageLength = strlen(message);
    strncpy(rpc.Message, message, rpc.dMessageLength);
    GetCoreInstance()->SendRPC(this->m_playerId, &rpc);
}

void mimp::CPlayer::setPlayerCheckpoint(const float x, const float y, const float z, const float size)
{
    this->m_checkpointPos[0] = x;
    this->m_checkpointPos[1] = y;
    this->m_checkpointPos[2] = z;
    this->m_checkpointSize = size;
    this->m_checkpointActive = true;

    ORPCSetCheckpoint rpc;
    rpc.x = x;
    rpc.y = y;
    rpc.z = z;
    rpc.radius = size;

    GetCoreInstance()->SendRPC(this->m_playerId, &rpc);
}

void mimp::CPlayer::disableCheckpoint(void)
{
    this->m_checkpointActive = false;
    this->m_checkpointPos[0] = 0.0f;
    this->m_checkpointPos[1] = 0.0f;
    this->m_checkpointPos[2] = 0.0f;
    this->m_checkpointSize = 0.0f;

    ORPCDisableCheckpoint rpc;
    GetCoreInstance()->SendRPC(this->m_playerId, &rpc);
}

void mimp::CPlayer::chatBubble(const uint16_t playerid, const uint32_t color, const float drawDistance, const uint32_t expiretime, uint8_t textLength, char* text) {
    ORPCChatBubble rpc;
    rpc.playerid = playerid;
    rpc.color = color;
    rpc.drawDistance = drawDistance;
    rpc.expiretime = expiretime;
    rpc.textLength = textLength;
    strncpy(rpc.text, text, textLength);
    GetCoreInstance()->SendRPC(this->m_playerId, &rpc);
}