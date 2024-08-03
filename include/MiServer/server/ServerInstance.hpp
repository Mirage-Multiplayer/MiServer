#ifndef __MISERVER_SERVERINSTANCE_HPP
#define __MISERVER_SERVERINSTANCE_HPP
#include "Server.hpp"

namespace mimp {
	namespace internal {
		namespace server {
			extern Server* g_ServerInstance;
			/**
			 * Get active server instance.
			 */
			Server* GetServerInstance(void);
			/**
			 * Set active server instance.
			 * @param svr - the server instance
			 */
			void SetServerInstance(Server* svr);
		}
	}
}
#endif