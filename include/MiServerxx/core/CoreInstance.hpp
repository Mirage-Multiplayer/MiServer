#pragma once
#include <MiServerxx/core/Core.hpp>

namespace mimp
{
	namespace internal
	{
		namespace server
		{
			extern CCore *g_CoreInstance;
			/**
			 * Get active core instance.
			 */
			CCore *GetCoreInstance(void);
			/**
			 * Set active core instance.
			 * @param c - the core instance
			 */
			void SetCoreInstance(CCore *c);
		}
	}
}
