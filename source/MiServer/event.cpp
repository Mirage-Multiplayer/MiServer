#include <MiServer/event.h>
#include <MiServerxx/core/Core.hpp>
#include <MiServerxx/event/EventPool.hpp>
#include <MiServerxx/event/EventTypes.hpp>

void mimp_server_event__onServerInit(mimp_core_t c, int (*cb)(void))
{
    reinterpret_cast<mimp::CCore *>(c)->getEventPool()->OnServerInit(cb);
}

void mimp_server_event__onServerExit(mimp_core_t c, int (*cb)(void))
{
    reinterpret_cast<mimp::CCore *>(c)->getEventPool()->OnServerExit(cb);
}

void mimp_server_event__onPlayerConnect(mimp_core_t c, int (*cb)(mimp_netgame_player_t player))
{
    reinterpret_cast<mimp::CCore *>(c)->getEventPool()->OnPlayerConnect(cb);
}

void mimp_server_event__onPlayerDisconnect(mimp_core_t c, int (*cb)(mimp_netgame_player_t player, int reason))
{
    reinterpret_cast<mimp::CCore *>(c)->getEventPool()->OnPlayerDisconnect(cb);
}

void mimp_server_event__onPlayerSpawn(mimp_core_t c, int (*cb)(mimp_netgame_player_t player))
{
    reinterpret_cast<mimp::CCore *>(c)->getEventPool()->OnPlayerSpawn(cb);
}

void mimp_server_event__onPlayerText(mimp_core_t c, int (*cb)(mimp_netgame_player_t player, const char *text))
{
    reinterpret_cast<mimp::CCore *>(c)->getEventPool()->OnPlayerText(cb);
}

void mimp_server_event__onPlayerCommandText(mimp_core_t c, int (*cb)(mimp_netgame_player_t player, const char *cmdtext))
{
    reinterpret_cast<mimp::CCore *>(c)->getEventPool()->OnPlayerCommandText(cb);
}