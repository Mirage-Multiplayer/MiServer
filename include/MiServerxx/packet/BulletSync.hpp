#ifndef __MISERVER_BULLETSYNC_HPP
#define __MISERVER_BULLETSYNC_HPP
#include <MiRak/NetworkTypes.h>

namespace mimp
{
	namespace internal
	{
		namespace packet
		{
			/**
			 * @brief Bullet Sync Packet
			 */
			void BulletSync(Packet *pkt);
		}
	}
}
#endif