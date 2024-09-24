#ifndef __MISERVER_AIMSYNC_HPP
#define __MISERVER_AIMSYNC_HPP
#include <MiRak/NetworkTypes.h>

namespace mimp
{
	namespace internal
	{
		namespace packet
		{
			/**
			 * @brief Aim Sync Packet
			 */
			void AimSync(Packet *pkt);
		}
	}
}
#endif