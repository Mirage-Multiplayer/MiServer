#ifndef __MISERVER_PASSANGERSYNC_HPP
#define __MISERVER_PASSANGERSYNC_HPP
#include <MiRak/NetworkTypes.h>

namespace mimp
{
	namespace internal
	{
		namespace packet
		{
			/**
			 * @brief Passenger Sync Packet
			 */
			void PassengerSync(Packet *pkt);
		}
	}
}
#endif