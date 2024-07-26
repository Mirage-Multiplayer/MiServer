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

				template<typename... Args>
				int Emit(uint16_t id, Args... args);
			private:
				EventQueue<OnServerInit_t> m_ServerInit;
				EventQueue<OnServerExit_t> m_ServerExit;
			};
		}
		
	}
}
#endif