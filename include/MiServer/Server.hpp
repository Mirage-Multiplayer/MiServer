#ifndef __MISERVER_SERVER_HPP
#define __MISERVER_SERVER_HPP
#include <string>
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
	private:
		ServerInfo m_info;
	};
}

#endif