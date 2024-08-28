#ifndef __MISERVER_SERVER_HPP
#define __MISERVER_SERVER_HPP
#include <MiRak/RakServer.h>
#include <MiRak/RakQuery.h>
#include <string>
#include <MiServer/event/EventPool.hpp>
#include <MiServer/vehicle/VehiclePool.hpp>
#include <MiServer/player/PlayerPool.hpp>
#include <MiServer/server/ServerConfig.hpp>

namespace mimp
{
	/** Struct that holds the server information
	 *
	 */
	struct ServerInfo
	{
	public:
		ServerInfo(const char *hostname, const char *gamemode, const char *lang, const unsigned int max_players);
		/**
		 * hostname
		 */
		std::string hostname;
		/**
		 * Gamemode
		 */
		std::string gamemode;
		/**
		 * Language
		 */
		std::string lang;
		/**
		 * Max Players
		 */
		unsigned int max_players;
	};

	/**
	 * Server class
	 */
	class Server
	{
	public:
		Server(const ServerInfo &info);
		Server(const ServerInfo &info, const ServerConfig &config);
		~Server();

		/**
		 * Init the server at the specified port.
		 * @param port
		 */
		int Init(uint16_t port);
		/**
		 * Shutdown Server and kill's the server instance.
		 */
		int Shutdown(void);
		/**
		 * Proccess the server Tick "Update"
		 * Should be called inside an infinite loop
		 */
		int ServerTick(void);

		/**
		 * Get server info.
		 */
		inline const ServerInfo getInfo(void) const
		{
			return this->m_info;
		}

		inline const ServerConfig getConfig(void) const
		{
			return this->m_cfg;
		}

		/**
		 * Get server EventPool instance.
		 */
		inline internal::event::EventPool *getEventPool(void) const
		{
			return this->m_eventPool;
		}

		/**
		 * Get server PlayerPool instance.
		 */
		inline internal::player::PlayerPool *getPlayerPool(void) const
		{
			return this->m_playerPool;
		}

		/**
		 * Get server RakServerInterface instance.
		 */
		inline RakServerInterface *getRakServer(void) const
		{
			return this->m_RakServer;
		}

		/**
		 * Get server VehiclePool instance.
		 */
		inline internal::vehicle::VehiclePool *getVehiclePool(void) const
		{
			return this->m_vehiclePool;
		}

	private:
		ServerInfo m_info;
		ServerConfig m_cfg;
		internal::event::EventPool *m_eventPool;
		internal::player::PlayerPool *m_playerPool;
		internal::vehicle::VehiclePool *m_vehiclePool;

		RakServerInterface *m_RakServer;

		bool m_initialized;
		uint16_t m_port;
	};
}

#endif