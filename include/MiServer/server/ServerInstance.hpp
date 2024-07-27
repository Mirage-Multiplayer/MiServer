#ifndef __MISERVER_SERVERINSTANCE_HPP
#define __MISERVER_SERVERINSTANCE_HPP
#include "Server.hpp"

namespace mimp {
	namespace internal {
		namespace server {
			extern Server* g_ServerInstance;
			Server* GetServerInstance(void);
			void SetServerInstance(Server* svr);
		}
	}
}
#endif