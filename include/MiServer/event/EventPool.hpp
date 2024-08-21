#ifndef __MISERVER_EVENTPOOL_HPP
#define __MISERVER_EVENTPOOL_HPP
#include <queue>
#include <MiServer/event/EventTypes.hpp>
#include <MiServer/event/EventQueue.hpp>

/* Event Pool
	Class who handle Event Queues and emit'em
*/
namespace mimp
{
	namespace internal
	{
		namespace event
		{
			class EventPool
			{
			public:
				EventPool();
				void OnServerInit(OnServerInit_t cb);

				void OnServerExit(OnServerExit_t cb);

				void OnPlayerConnect(OnPlayerConnect_t cb);

				void OnPlayerDisconnect(OnPlayerDisconnect_t cb);

				void OnPlayerSpawn(OnPlayerSpawn_t cb);

				/*
				 * Receives a event ID and the context, e.g, a fucking struct with arguments.
				 */
				int Emit(uint16_t id, void *ctx);

			private:
				EventQueue<OnServerInit_t> *m_ServerInit;
				EventQueue<OnServerExit_t> *m_ServerExit;
				EventQueue<OnPlayerConnect_t> *m_PlayerConnect;
				EventQueue<OnPlayerDisconnect_t> *m_PlayerDisconnect;
				EventQueue<OnPlayerSpawn_t> *m_PlayerSpawn;
			};
		}

	}
}
#endif