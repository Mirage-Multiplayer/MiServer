#ifndef __MISERVER_UNOCCUPIEDSYNC_HPP
#define __MISERVER_UNOCCUPIEDSYNC_HPP
#include <MiRak/NetworkTypes.h>

namespace mimp {
	namespace internal {
		namespace packet {
			void UnoccupiedSync(Packet* pkt);
		}
	}
}

#endif