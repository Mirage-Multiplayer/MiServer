#ifndef __MISERVER_EVENTPOOL_HPP
#define __MISERVER_EVENTPOOL_HPP
#include <queue>
#include "EventTypes.hpp"
#include "EventQueue.hpp"

namespace mimp {
	namespace internal{
		namespace event {
			class EventPool {
			public:
				EventPool() = default;
				inline void OnServerInit(OnServerInit_t cb) {
					this->m_ServerInit.Add(cb);
				}

				inline void OnServerExit(OnServerExit_t cb) {
					this->m_ServerExit.Add(cb);
				}

				inline void OnPlayerConnect(OnPlayerConnect_t cb) {
					this->m_PlayerConnect.Add(cb);
				}

				inline void OnPlayerDisconnect(OnPlayerDisconnect_t cb) {
					this->m_PlayerDisconnect.Add(cb);
				}

				template<typename... Args>
				int Emit(uint16_t id, Args... args) {
					switch (id) {
					case SERVER_EVENT_SERVERINIT: {
						this->m_ServerInit.CallVoid();
						break;
					}
					case SERVER_EVENT_SERVEREXIT: {
						this->m_ServerExit.CallVoid();
						break;
					}
					case SERVER_EVENT_PLAYERCONNECT: {
						this->m_PlayerConnect.Call(args...);
						break;
					}
					case SERVER_EVENT_PLAYERDISCONNECT: {
						this->m_PlayerDisconnect.Call(args...);
						break;
					}
					default: {
						return -1;
					}
					}
				}
			private:
				EventQueue<OnServerInit_t> m_ServerInit;
				EventQueue<OnServerExit_t> m_ServerExit;
				EventQueue<OnPlayerConnect_t> m_PlayerConnect;
				EventQueue<OnPlayerDisconnect_t> m_PlayerDisconnect;
			};
		}
		
	}
}
#endif