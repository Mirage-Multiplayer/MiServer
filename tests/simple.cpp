#include <iostream>
#include <thread>
#include <MiServer/server/Server.hpp>
#include <MiServer/event/EventTypes.hpp>
#include <MiServer/event/EventPool.hpp>

#ifdef _WIN32
#pragma comment(lib, "ws2_32")
#endif

int hnd(SOCKET sListen, int iAddrSize, struct sockaddr_in client, char *pBuffer)
{
	std::cout << "Query incoming...\n";
	return 1;
}

int main(void)
{
	// Config server info
	mimp::ServerInfo info("Hostname", "gamemode", "PT/BR", 200);
	mimp::ServerConfig cfg;

	cfg.zoneNames = true;
	cfg.gravity = 0.008f;
	cfg.disableEnterExits = true;
	// Create Server instance
	mimp::Server server(info);

	// Define callbacks & handlers
	RakNet::RakQuery::setHandler(hnd);

	server.getEventPool()->OnServerInit([](void) -> int
										{								
		const int idx = mimp::Vehicle::Create(411, 368.3278f,2538.5803f,16.6275f,20.5909f, -1, -1, 10000, true, false, 0);
		std::cout << "Vehicle id: " << idx << " created.\n";
		std::cout << "ServerInit\n";
		return 1; });
	server.getEventPool()->OnPlayerSpawn([](mimp::Player *p) -> int
										 {
		std::cout << "Player ID " << p->getPlayerId() << " Spawned\n";
		p->clientMessage(0xCD5C5CFF, "Welcome");
		return 1; });

	server.getEventPool()->OnPlayerText([](mimp::Player *p, const char *text) -> int
										{
		p->clientMessage(0xCD5C5CFF, text);
		if (std::string(text).find("infernus") != -1)
		{
			float x, y, z;
			p->getPos(x, y, z);
			float r = p->getRotation();
			mimp::Vehicle::Create(411, x,y,z,20.5909f, -1, -1, 10000, true, false, 0);

		}; return 1; });

	server.getEventPool()->OnPlayerUpdate([](mimp::Player *p) -> int
										  { 
			std::cout << "Player Update\n";
											return 1; });
	// Initialize server
	server.Init(7777);

	while (1)
	{
		server.ServerTick();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	return 1;
}