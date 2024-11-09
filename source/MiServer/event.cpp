#include <MiServer/event.h>
#include <MiServerxx/core/Core.hpp>
#include <MiServerxx/event/EventPool.hpp>

using namespace mimp::internal::event;

void mimp_server_event__onServerInit(mimp_core_t c, int (*cb)(void))
{
    MIMP_GET_EVENT(SERVERINIT, reinterpret_cast<mimp::CCore*>(c)->getEventPool());
    SERVERINIT->OnCall(cb);
}

void mimp_server_event__onServerExit(mimp_core_t c, int (*cb)(void))
{

    MIMP_GET_EVENT(SERVEREXIT, reinterpret_cast<mimp::CCore*>(c)->getEventPool());
    SERVEREXIT->OnCall(cb);
}

void mimp_server_event__onPlayerConnect(mimp_core_t c, int (*cb)(mimp_netgame_player_t player))
{
    MIMP_GET_EVENT(PLAYERCONNECT, reinterpret_cast<mimp::CCore*>(c)->getEventPool());
    PLAYERCONNECT->OnCall(cb);
}

void mimp_server_event__onPlayerDisconnect(mimp_core_t c, int (*cb)(mimp_netgame_player_t player, int reason))
{
    MIMP_GET_EVENT(PLAYERDISCONNECT, reinterpret_cast<mimp::CCore*>(c)->getEventPool());
    PLAYERDISCONNECT->OnCall(cb);
}

void mimp_server_event__onPlayerSpawn(mimp_core_t c, int (*cb)(mimp_netgame_player_t player))
{
    MIMP_GET_EVENT(PLAYERSPAWN, reinterpret_cast<mimp::CCore*>(c)->getEventPool());
    PLAYERSPAWN->OnCall(cb);
}

void mimp_server_event__onPlayerText(mimp_core_t c, int (*cb)(mimp_netgame_player_t player, const char *text))
{
    MIMP_GET_EVENT(PLAYERTEXT, reinterpret_cast<mimp::CCore*>(c)->getEventPool());
    PLAYERTEXT->OnCall(cb);
}

void mimp_server_event__onPlayerCommandText(mimp_core_t c, int (*cb)(mimp_netgame_player_t player, const char *cmdtext))
{
    MIMP_GET_EVENT(COMMANDTEXT, reinterpret_cast<mimp::CCore*>(c)->getEventPool());
    COMMANDTEXT->OnCall(cb);
}