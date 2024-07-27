#ifndef __MISERVER_VEHICLESYNC_HPP
#define __MISERVER_VEHICLESYNC_HPP
#include <MiRak/NetworkTypes.h>

namespace mimp {
	namespace internal {
		namespace packet {
			void VehicleSync(Packet* pkt);
		}
	}
}
#endif