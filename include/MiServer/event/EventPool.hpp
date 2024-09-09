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
				void OnServerInit(OnServerInit_t cb)
				{
					this->m_ServerInit = cb;
				}

				void OnServerExit(OnServerExit_t cb)
				{
					this->m_ServerExit = cb;
				}

				void OnPlayerConnect(OnPlayerConnect_t cb)
				{
					this->m_PlayerConnect = cb;
				}

				void OnPlayerDisconnect(OnPlayerDisconnect_t cb)
				{
					this->m_PlayerDisconnect = cb;
				}

				void OnPlayerSpawn(OnPlayerSpawn_t cb)
				{
					this->m_PlayerSpawn = cb;
				}

				void OnPlayerText(OnPlayerText_t cb)
				{
					this->m_PlayerText = cb;
				}

				void OnPlayerCommandText(OnPlayerCommandText_t cb)
				{
					this->m_PlayerCMDText = cb;
				}

				void OnPlayerUpdate(OnPlayerUpdate_t cb)
				{
					this->m_PlayerUpdate = cb;
				}

				/*
				 * Receives a event ID and the context, e.g, a fucking struct with arguments.
				 */
				int Emit(uint16_t id, void *ctx);

			private:
				OnServerInit_t m_ServerInit;
				OnServerExit_t m_ServerExit;
				OnPlayerConnect_t m_PlayerConnect;
				OnPlayerDisconnect_t m_PlayerDisconnect;
				OnPlayerSpawn_t m_PlayerSpawn;
				OnPlayerText_t m_PlayerText;
				OnPlayerCommandText_t m_PlayerCMDText;
				OnPlayerUpdate_t m_PlayerUpdate;
			};
		}

	}
}
#endif