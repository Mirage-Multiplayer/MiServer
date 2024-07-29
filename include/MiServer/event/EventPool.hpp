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
				EventPool();
				void OnServerInit(EventCallback_t cb);

				void OnServerExit(EventCallback_t cb);

				void OnPlayerConnect(EventCallback_t cb);

				void OnPlayerDisconnect(EventCallback_t cb);

				void OnPlayerSpawn(EventCallback_t cb);

				void OnPlayerWeaponShot(EventCallback_t cb);
				
				int Emit(uint16_t id, void* ctx);
			private:
				EventQueue* m_ServerInit;
				EventQueue* m_ServerExit;
				EventQueue* m_PlayerConnect;
				EventQueue* m_PlayerDisconnect;
				EventQueue* m_PlayerSpawn;
				EventQueue* m_PlayerWeaponShoot;
			};
		}
		
	}
}
#endif