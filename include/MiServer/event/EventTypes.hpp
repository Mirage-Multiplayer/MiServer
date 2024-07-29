#ifndef __MISERVER_EVENTTYPES_HPP
#define __MISERVER_EVENTTYPES_HPP
#include <functional>
#include "../player/Player.hpp"

/* EventType
	Store information about events, their callbacks and their params
*/
namespace mimp {
	namespace internal {
		namespace event {
			enum {
				SERVER_EVENT_SERVERINIT = 0,
				SERVER_EVENT_SERVEREXIT = 1,
				SERVER_EVENT_PLAYERCONNECT,
				SERVER_EVENT_PLAYERDISCONNECT,
				SERVER_EVENT_PLAYERSPAWN
			};

			// Disclaimer: I wanted to make this as dynamic as possible, and this was the way I found
			using OnServerInit_t = std::function<int()>;

			using OnServerExit_t = std::function<int()>;

			using OnPlayerConnect_t = std::function<int(Player*)>;
			using OnPlayerConnect_params = struct {
				Player* player;
			};

			using OnPlayerDisconnect_t = std::function<int(Player*)>;
			using OnPlayerDisconnect_params = struct {
				Player* player;
			};

			using OnPlayerSpawn_t = std::function<int(Player*)>;
			using OnPlayerSpawn_params = struct {
				Player* player;
			};
		}	
	}
}
#endif