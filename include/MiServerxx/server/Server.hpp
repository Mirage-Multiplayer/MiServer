#ifndef __MISERVER_SERVER_HPP
#define __MISERVER_SERVER_HPP
#include <MiRak/RakServer.h>
#include <MiRak/RakQuery.h>
#include <string>
#include <MiServerxx/event/EventPool.hpp>
#include <MiServerxx/server/ServerConfig.hpp>
#include <MiServerxx/netgame/NetGame.hpp>
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
	class CServer
	{
	public:
		CServer(const ServerInfo &info);
		CServer(const ServerInfo &info, const ServerConfig &config);
		~CServer();

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

		inline mimp::CNetGame *GetNetGame()
		{
			return this->m_pNetGame;
		}
		/**
		 * Get server RakServerInterface instance.
		 */
		inline RakServerInterface *getRakServer(void) const
		{
			return this->m_pRakServer;
		}

		inline mimp::internal::event::CEventPool *getEventPool(void) const
		{
			return this->m_pEventPool;
		}

	private:
		ServerInfo m_info;
		ServerConfig m_cfg;
		mimp::CNetGame *m_pNetGame;
		mimp::internal::event::CEventPool *m_pEventPool;

		RakServerInterface *m_pRakServer;

		bool m_initialized;
		uint16_t m_port;
	};
}

#endif