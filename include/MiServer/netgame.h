#ifndef __MISERVER_NETGAME_H
#define __MISERVER_NETGAME_H
#include <MiServer/types.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C"
{
#endif
    mimp_netgame_player_t mimp_netgame__getPlayer(mimp_netgame_t game, int playerid);
    int mimp_netgame_player__getId(mimp_netgame_player_t);
    void mimp_netgame_player__getNickName(mimp_netgame_player_t, char *nickname);
    void mimp_netgame_player__getIP(mimp_netgame_player_t, char *ip);
    int mimp_netgame_player__getPort(mimp_netgame_player_t);
    int mimp_netgame_player__getScore(mimp_netgame_player_t);
    int mimp_netgame_player__getPing(mimp_netgame_player_t);
    void mimp_netgame_player__getPos(mimp_netgame_player_t, float *x, float *y, float *z);
    void mimp_netgame_player__getRotation(mimp_netgame_player_t, float *r);
    int mimp_netgame_player__getCurrentVehicle(mimp_netgame_player_t);
    int mimp_netgame_player__getSkin(mimp_netgame_player_t);
    void mimp_netgame_player__getSpawn(mimp_netgame_player_t, float *x, float *y, float *z);
    int mimp_netgame_player__getInteriorId(mimp_netgame_player_t);
    void mimp_netgame_player__getCheckpointPos(mimp_netgame_player_t, float *x, float *y, float *z);
    float mimp_netgame_player__getCheckpointSize(mimp_netgame_player_t);
    int mimp_netgame_player__getFightingStyle(mimp_netgame_player_t);
    int mimp_netgame_player__getHealth(mimp_netgame_player_t, float *d);
    int mimp_netgame_player__getArmour(mimp_netgame_player_t, float *d);
    void mimp_netgame_player__setHealth(mimp_netgame_player_t, float value);
    void mimp_netgame_player__setArmour(mimp_netgame_player_t, float value);
    void mimp_netgame_player__setSkin(mimp_netgame_player_t, int skinid);
    void mimp_netgame_player__setSpawn(mimp_netgame_player_t, float x, float y, float z);
    void mimp_netgame_player__setPos(mimp_netgame_player_t, float x, float y, float z);
    void mimp_netgame_player__setRotation(mimp_netgame_player_t, float r);
    void mimp_netgame_player__setColor(mimp_netgame_player_t, int color);
    void mimp_netgame_player__clientMessage(mimp_netgame_player_t, int color, const char *message);
    void mimp_netgame_player__setCheckpoint(mimp_netgame_player_t, float x, float y, float z, float size);
    void mimp_netgame_player__disableCheckpoint(mimp_netgame_player_t);
    int mimp_netgame_player__inCheckpoint(mimp_netgame_player_t);

    mimp_netgame_vehicle_t mimp_netgame__getVehicle(mimp_netgame_t game, int vehicleid);
    int mimp_netgame_vehicle__create(mimp_netgame_t game, int modelid, float x, float y, float z, float r, int color1, int color2, int respawn_delay, bool respawn, bool siren, int interior);
    int mimp_netgame_vehicle__getId(mimp_netgame_vehicle_t);
    int mimp_netgame_vehicle__getModelId(mimp_netgame_vehicle_t);
    void mimp_netgame_vehicle__getPos(mimp_netgame_vehicle_t, float *x, float *y, float *z);
    void mimp_netgame_vehicle__getRotation(mimp_netgame_vehicle_t, float *r);
    void mimp_netgame_vehicle__getHealth(mimp_netgame_vehicle_t, float *health);
    void mimp_netgame_vehicle__setHealth(mimp_netgame_vehicle_t, float health);
    void mimp_netgame_vehicle__setPos(mimp_netgame_vehicle_t, float x, float y, float z);
    void mimp_netgame_vehicle__setRotation(mimp_netgame_vehicle_t, float r);
    void mimp_netgame_vehicle__respawn(mimp_netgame_vehicle_t);
#ifdef __cplusplus
}
#endif
#endif