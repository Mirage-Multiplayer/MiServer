#include "MiServer.hpp"
#include "Server.hpp"
#include "event/EventPool.hpp"

mimp::ServerInfo::ServerInfo(const char* hostname, const char* gamemode, const char* lang, const unsigned int max_players) :
	hostname(hostname), gamemode(gamemode), lang(lang), max_players(max_players)
{
}

mimp::Server::Server(const ServerInfo& info): m_info(info)
{
}