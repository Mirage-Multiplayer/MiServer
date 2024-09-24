#ifndef __MISERVER_EVENT_H
#define __MISERVER_EVENT_H
#include <MiServer/types.h>
#ifdef __cplusplus
extern "C"
{
#endif
    void mimp_server_event__onServerInit(mimp_core_t core, int (*cb)(void));
    void mimp_server_event__onServerExit(mimp_core_t core, int (*cb)(void));
    void mimp_server_event__onPlayerConnect(mimp_core_t c, int (*cb)(mimp_netgame_player_t player));
    void mimp_server_event__onPlayerDisconnect(mimp_core_t c, int (*cb)(mimp_netgame_player_t player, int reason));
    void mimp_server_event__onPlayerSpawn(mimp_core_t c, int (*cb)(mimp_netgame_player_t player));
    void mimp_server_event__onPlayerText(mimp_core_t c, int (*cb)(mimp_netgame_player_t player, const char *text));
    void mimp_server_event__onPlayerCommandText(mimp_core_t c, int (*cb)(mimp_netgame_player_t player, const char *cmdtext));

#ifdef __cplusplus
}
#endif
#endif