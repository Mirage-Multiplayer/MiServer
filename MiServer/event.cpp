#include <MiServer/event.h>
#include <MiServerxx/server/Server.hpp>
#include <MiServerxx/event/EventPool.hpp>
#include <MiServerxx/event/EventTypes.hpp>

void mimp_server_event__onServerInit(mimp_server_t server, int (*cb)(void))
{
    reinterpret_cast<mimp::CServer *>(server)->getEventPool()->OnServerInit(cb);
}

void mimp_server_event__onServerExit(mimp_server_t server, int (*cb)(void))
{
    reinterpret_cast<mimp::CServer *>(server)->getEventPool()->OnServerExit(cb);
}

void mimp_server_event__onPlayerConnect(mimp_server_t server, int (*cb)(mimp_netgame_player_t player))
{
    reinterpret_cast<mimp::CServer *>(server)->getEventPool()->OnPlayerConnect(cb);
}

void mimp_server_event__onPlayerDisconnect(mimp_server_t server, int (*cb)(mimp_netgame_player_t player, int reason))
{
    reinterpret_cast<mimp::CServer *>(server)->getEventPool()->OnPlayerDisconnect(cb);
}

void mimp_server_event__onPlayerSpawn(mimp_server_t server, int (*cb)(mimp_netgame_player_t player))
{
    reinterpret_cast<mimp::CServer *>(server)->getEventPool()->OnPlayerSpawn(cb);
}

void mimp_server_event__onPlayerText(mimp_server_t server, int (*cb)(mimp_netgame_player_t player, const char *text))
{
    reinterpret_cast<mimp::CServer *>(server)->getEventPool()->OnPlayerText(cb);
}

void mimp_server_event__onPlayerCommandText(mimp_server_t server, int (*cb)(mimp_netgame_player_t player, const char *cmdtext))
{
    reinterpret_cast<mimp::CServer *>(server)->getEventPool()->OnPlayerCommandText(cb);
}