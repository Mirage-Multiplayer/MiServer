#pragma once
#include <functional>
#include <MiServerxx/event/Event.hpp>
#include <MiServerxx/netgame/Player.hpp>
#include <MiServerxx/netgame/Vehicle.hpp>

/* EventType
	Store information about events, their callbacks and their params
*/
namespace mimp
{
	namespace internal
	{
		namespace event
		{
			enum
			{
				SERVER_EVENT_SERVERINIT = 0,
				SERVER_EVENT_SERVEREXIT = 1,
				SERVER_EVENT_PLAYERCONNECT,
				SERVER_EVENT_PLAYERDISCONNECT,
				SERVER_EVENT_PLAYERSPAWN,
				SERVER_EVENT_PLAYERDEATH,
				SERVER_EVENT_PLAYERTEXT,
				SERVER_EVENT_COMMANDTEXT,
				SERVER_EVENT_PLAYERUPDATE
			};

			using SERVER_EVENT_SERVERINIT_T = CEvent<>;
			using SERVER_EVENT_SERVEREXIT_T = CEvent<>;
			using SERVER_EVENT_PLAYERCONNECT_T = CEvent<CPlayer*>;
			using SERVER_EVENT_PLAYERDISCONNECT_T = CEvent<CPlayer*, int>;
			using SERVER_EVENT_PLAYERSPAWN_T = CEvent<CPlayer*>;
			using SERVER_EVENT_PLAYERDEATH_T = CEvent<CPlayer*, CPlayer*, int>;
			using SERVER_EVENT_PLAYERTEXT_T = CEvent<CPlayer*, const char*>;
			using SERVER_EVENT_COMMANDTEXT_T = CEvent<CPlayer*, char*>;
			using SERVER_EVENT_PLAYERUPDATE_T = CEvent<CPlayer*>;
		}
	}
}