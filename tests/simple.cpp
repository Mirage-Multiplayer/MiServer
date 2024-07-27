#include <iostream>
#include <thread>
#include "server/Server.hpp"
#ifdef _WIN32
#pragma comment(lib, "ws2_32")
#endif

int hnd(SOCKET sListen, int iAddrSize, struct sockaddr_in client, char* pBuffer) {
	std::cout << "Query Incomming...\n";
	return 1;
}

int main(void) {
	mimp::ServerInfo info("Hostname", "gamemode", "PT/BR", 200);
	mimp::Server server(info);
	server.Init(7777);
	RakNet::RakQuery::setHandler(hnd);
	while (1) {
		server.ServerTick();
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}

	return 1;
}