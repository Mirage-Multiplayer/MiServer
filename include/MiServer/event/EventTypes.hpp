#ifndef __MISERVER_EVENTTYPES_HPP
#define __MISERVER_EVENTTYPES_HPP
#include <functional>
namespace mimp {
	namespace internal {
		namespace event {
			enum {
				SERVER_EVENT_SERVERINIT = 0,
				SERVER_EVENT_SERVEREXIT = 1,
				SERVER_EVENT_PLAYERCONNECT,
				SERVER_EVENT_PLAYEREDISCONNECT,
			};

			using OnServerInit_t = std::function<int(void)>;
			using OnServerExit_t = std::function<int(void)>;
			using OnPlayerConnect_t = std::function<int(const int)>;
			using OnPlayerDisconnect_t = std::function<int(const int)>;
		}	
	}
}
#endif