#ifndef __MISERVER_SERVER_HPP
#define __MISERVER_SERVER_HPP
#include <MiRak/RakServer.h>
#include <MiRak/RakQuery.h>
#include <string>
#include "event/EventPool.hpp"
#include "vehicle/VehiclePool.hpp"
#include "player/PlayerPool.hpp"

namespace mimp {
	struct ServerInfo {
	public:
		ServerInfo(const char* hostname, const char* gamemode, const char* lang, const unsigned int max_players);
		std::string hostname;
		std::string gamemode;
		std::string lang;
		unsigned int max_players;
	};

	class Server {
	public:
		Server(const ServerInfo& info);
		int Init(uint16_t port);
		int ServerTick(void);
		inline const internal::event::EventPool* events() {
			return this->m_eventPool;
		}

		inline const ServerInfo getInfo(void) const {
			return this->m_info;
		}

		inline internal::player::PlayerPool* getPlayerPool(void) const {
			return this->m_playerPool;
		}

		inline RakServerInterface* getRakServer(void) const {
			return this->m_RakServer;
		}

		inline internal::vehicle::VehiclePool* getVehiclePool(void) const {
			return this->m_vehiclePool;
		}

	private:
		ServerInfo m_info;

		internal::event::EventPool* m_eventPool;
		internal::player::PlayerPool* m_playerPool;
		internal::vehicle::VehiclePool* m_vehiclePool;

		RakServerInterface* m_RakServer;

		bool m_initialized;
		uint16_t m_port;

	};
}

#endif