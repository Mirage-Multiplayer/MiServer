#ifndef __MISERVER_POSITIONSYNC_HPP
#define __MISERVER_POSITIONSYNC_HPP

namespace mimp {
	namespace internal {
		namespace packet {
			void UpdatePosition(int iPlayerID, float fX, float fY, float fZ);
		}
	}
}
#endif