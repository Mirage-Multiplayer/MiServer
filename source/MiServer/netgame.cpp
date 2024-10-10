#include <MiServer/netgame.h>
#include <MiServerxx/netgame/Player.hpp>
#include <MiServerxx/netgame/Vehicle.hpp>
#include <MiServerxx/netgame/NetGame.hpp>

mimp_netgame_player_t mimp_netgame__getPlayer(mimp_netgame_t game, int playerid)
{
    return reinterpret_cast<mimp::CNetGame *>(game)->GetPlayerPool()->GetAt(playerid);
}

int mimp_netgame_player__getId(mimp_netgame_player_t player)
{
    return reinterpret_cast<mimp::CPlayer *>(player)->getPlayerId();
}

int mimp_netgame_player__getScore(mimp_netgame_player_t player)
{
    return reinterpret_cast<mimp::CPlayer *>(player)->getScore();
}

void mimp_netgame_player__getNickName(mimp_netgame_player_t player, char *nickname)
{
    strcpy(nickname, reinterpret_cast<mimp::CPlayer *>(player)->getNickName().c_str());
}

void mimp_netgame_player__getIP(mimp_netgame_player_t player, char *ip)
{
    strcpy(ip, reinterpret_cast<mimp::CPlayer *>(player)->getIP().c_str());
}

void mimp_netgame_player__getPos(mimp_netgame_player_t player, float *x, float *y, float *z)
{
    reinterpret_cast<mimp::CPlayer *>(player)->getPos(*x, *y, *z);
}

void mimp_netgame_player__getRotation(mimp_netgame_player_t player, float *r)
{
    *r = reinterpret_cast<mimp::CPlayer *>(player)->getRotation();
}

int mimp_netgame_player__getPing(mimp_netgame_player_t player)
{
    return reinterpret_cast<mimp::CPlayer *>(player)->getPing();
}

int mimp_netgame_player__getCurrentVehicle(mimp_netgame_player_t player)
{
    return reinterpret_cast<mimp::CPlayer *>(player)->getCurrentVehicle();
}

int mimp_netgame_player__getSkin(mimp_netgame_player_t player)
{
    return reinterpret_cast<mimp::CPlayer *>(player)->getSkin();
}

void mimp_netgame_player__getSpawn(mimp_netgame_player_t player, float *x, float *y, float *z)
{
    reinterpret_cast<mimp::CPlayer *>(player)->getSpawn(*x, *y, *z);
}

int mimp_netgame_player__getInteriorId(mimp_netgame_player_t player)
{
    return reinterpret_cast<mimp::CPlayer *>(player)->getInteriorId();
}

void mimp_netgame_player__getCheckpointPos(mimp_netgame_player_t player, float *x, float *y, float *z)
{
    reinterpret_cast<mimp::CPlayer *>(player)->getCheckpointPos(*x, *y, *z);
}

float mimp_netgame_player__getCheckpointSize(mimp_netgame_player_t player)
{
    return reinterpret_cast<mimp::CPlayer *>(player)->getCheckpointSize();
}

int mimp_netgame_player__getFightingStyle(mimp_netgame_player_t player)
{
    return reinterpret_cast<mimp::CPlayer *>(player)->getFightingStyle();
}

int mimp_netgame_player__getHealth(mimp_netgame_player_t player, float *d)
{
    *d = reinterpret_cast<mimp::CPlayer *>(player)->getHealth();
    return 1;
}

int mimp_netgame_player__getArmour(mimp_netgame_player_t player, float *d)
{
    *d = reinterpret_cast<mimp::CPlayer *>(player)->getArmour();
    return 1;
}

void mimp_netgame_player__setHealth(mimp_netgame_player_t player, float value)
{
    reinterpret_cast<mimp::CPlayer *>(player)->setHealth(value);
}

void mimp_netgame_player__setArmour(mimp_netgame_player_t player, float value)
{
    reinterpret_cast<mimp::CPlayer *>(player)->setArmour(value);
}

void mimp_netgame_player__setSkin(mimp_netgame_player_t player, int skinid)
{
    reinterpret_cast<mimp::CPlayer *>(player)->setSkin(skinid);
}

void mimp_netgame_player__setSpawn(mimp_netgame_player_t player, float x, float y, float z)
{
    reinterpret_cast<mimp::CPlayer *>(player)->setSpawn(x, y, z);
}

void mimp_netgame_player__setPos(mimp_netgame_player_t player, float x, float y, float z)
{
    reinterpret_cast<mimp::CPlayer *>(player)->setPos(x, y, z);
}

void mimp_netgame_player__setRotation(mimp_netgame_player_t player, float r)
{
    reinterpret_cast<mimp::CPlayer *>(player)->setRotation(r);
}

void mimp_netgame_player__setColor(mimp_netgame_player_t player, int color)
{
    reinterpret_cast<mimp::CPlayer *>(player)->setColor(color);
}

void mimp_netgame_player__clientMessage(mimp_netgame_player_t player, int color, const char *message)
{
    reinterpret_cast<mimp::CPlayer *>(player)->clientMessage(color, message);
}

void mimp_netgame_player__setCheckpoint(mimp_netgame_player_t player, float x, float y, float z, float size)
{
    reinterpret_cast<mimp::CPlayer *>(player)->setPlayerCheckpoint(x, y, z, size);
}

void mimp_netgame_player__disableCheckpoint(mimp_netgame_player_t player)
{
    reinterpret_cast<mimp::CPlayer *>(player)->disableCheckpoint();
}

int mimp_netgame_player__inCheckpoint(mimp_netgame_player_t player)
{
    return reinterpret_cast<mimp::CPlayer *>(player)->isPlayerInCheckpoint();
}

// Vehicle section
mimp_netgame_vehicle_t mimp_netgame__getVehicle(mimp_netgame_t game, int vehicleid)
{
    return reinterpret_cast<mimp::CNetGame *>(game)->GetVehiclePool()->GetAt(vehicleid);
}

int mimp_netgame_vehicle__create(mimp_netgame_t game, int modelid, float x, float y, float z, float r, int color1, int color2, int respawn_delay, bool respawn, bool siren, int interior)
{
    return mimp::CVehicle::Create(modelid, x, y, z, r, color1, color2, respawn_delay, respawn, siren, interior);
}

int mimp_netgame_vehicle__getId(mimp_netgame_vehicle_t vehicle)
{
    return reinterpret_cast<mimp::CVehicle *>(vehicle)->getId();
}

int mimp_netgame_vehicle__getModelId(mimp_netgame_vehicle_t vehicle)
{
    return reinterpret_cast<mimp::CVehicle *>(vehicle)->getModelId();
}

void mimp_netgame_vehicle__getPos(mimp_netgame_vehicle_t vehicle, float *x, float *y, float *z)
{
    reinterpret_cast<mimp::CVehicle *>(vehicle)->getPosition(*x, *y, *z);
}

void mimp_netgame_vehicle__getRotation(mimp_netgame_vehicle_t vehicle, float *r)
{
    *r = reinterpret_cast<mimp::CVehicle *>(vehicle)->getRotation();
}

void mimp_netgame_vehicle__getHealth(mimp_netgame_vehicle_t vehicle, float *health)
{
    *health = reinterpret_cast<mimp::CVehicle *>(vehicle)->getHealth();
}

void mimp_netgame_vehicle__setHealth(mimp_netgame_vehicle_t vehicle, float health)
{
    reinterpret_cast<mimp::CVehicle *>(vehicle)->setHealth(health);
}

void mimp_netgame_vehicle__setSpawn(mimp_netgame_vehicle_t vehicle, float x, float y, float z)
{
    reinterpret_cast<mimp::CVehicle *>(vehicle)->setPosition(x, y, z);
}

void mimp_netgame_vehicle__setPos(mimp_netgame_vehicle_t vehicle, float x, float y, float z)
{
    reinterpret_cast<mimp::CVehicle *>(vehicle)->setPosition(x, y, z);
}
