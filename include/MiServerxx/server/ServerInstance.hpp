#ifndef __MISERVER_SERVERINSTANCE_HPP
#define __MISERVER_SERVERINSTANCE_HPP
#include <MiServerxx/server/ServerInstance.hpp>
#include <MiServerxx/server/Server.hpp>

namespace mimp
{
	namespace internal
	{
		namespace server
		{
			extern CServer *g_ServerInstance;
			/**
			 * Get active server instance.
			 */
			CServer *GetServerInstance(void);
			/**
			 * Set active server instance.
			 * @param svr - the server instance
			 */
			void SetServerInstance(CServer *svr);
		}
	}
}
#endif