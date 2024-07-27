#ifndef __MISERVER_PLAYERSYNC_HPP
#define __MISERVER_PLAYERSYNC_HPP
#include <MiRak/NetworkTypes.h>

namespace mimp {
	namespace internal {
		namespace packet {
			void PlayerSync(Packet* pkt);
		}
	}
}
#endif