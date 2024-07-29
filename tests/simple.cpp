#include <iostream>
#include <thread>
#include "server/Server.hpp"
#include "event/EventTypes.hpp"
#include "event/EventPool.hpp"

#ifdef _WIN32
#pragma comment(lib, "ws2_32")
#endif

int hnd(SOCKET sListen, int iAddrSize, struct sockaddr_in client, char* pBuffer) {
	std::cout << "Query Incomming...\n";
	return 1;
}

int main(void) {
	// Config server info
	mimp::ServerInfo info("Hostname", "gamemode", "PT/BR", 200);

	// Create Server instance
	mimp::Server server(info);

	// Define callbacks & handlers
	RakNet::RakQuery::setHandler(hnd);

	server.getEventPool()->OnServerInit([](void* ctx) -> int {
		std::cout << "ServerInit\n";
		return 1;
		});

	server.getEventPool()->OnPlayerSpawn([](void* ctx) -> int {
		std::cout << "PlayerSpawn\n";
		return 1;
		});

	// Initialize server
	server.Init(7777);

	while (1) {
		server.ServerTick();
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}

	return 1;
}