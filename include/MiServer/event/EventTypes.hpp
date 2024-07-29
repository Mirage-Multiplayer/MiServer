#ifndef __MISERVER_EVENTTYPES_HPP
#define __MISERVER_EVENTTYPES_HPP
#include <functional>
#include "../player/Player.hpp"

#define MAX_EVENTS_PER_QUEUE 200

namespace mimp {
	namespace internal {
		namespace event {
			enum {
				SERVER_EVENT_SERVERINIT = 0,
				SERVER_EVENT_SERVEREXIT = 1,
				SERVER_EVENT_PLAYERCONNECT,
				SERVER_EVENT_PLAYERDISCONNECT,
				SERVER_EVENT_PLAYERSPAWN,
				SERVER_EVENT_PLAYERWEAPONSHOT
			};

			using EventCallback_t = std::function<int(void*)>;
		}	
	}
}
#endif