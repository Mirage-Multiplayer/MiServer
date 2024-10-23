#include <iostream>
#include <thread>
#include <MiServerxx/core/Core.hpp>
#include <MiServerxx/event/EventTypes.hpp>
#include <MiServerxx/event/EventPool.hpp>
#include <MiServerxx/util/strformat.hpp>
#include <MiServerxx/query/SAMPQuery.hpp>

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
	mimp::ServerInfo info("Mi:MP Test Server", "simplexx", "PT/BR", 200);
	mimp::ServerConfig cfg;

	cfg.zoneNames = true;
	cfg.gravity = 0.008f;
	cfg.disableEnterExits = true;
	// Create Server instance
	mimp::CCore server(info, cfg);

	// Define callbacks & handlers
	RakNet::RakQuery::setHandler(mimp::internal::query::SAMPQueryHandler);

	server.getEventPool()->OnServerInit([](void) -> int
										{								
		const int idx = mimp::CVehicle::Create(411, 368.3278f,2538.5803f,16.6275f,20.5909f, -1, -1, 10000, true, false, 0);
		std::cout << "Vehicle id: " << idx << " created.\n";
		std::cout << "ServerInit\n";
		return 1; });
	server.getEventPool()->OnPlayerSpawn([](mimp::CPlayer *p) -> int
										 {
		std::cout << "Player ID " << p->getPlayerId() << " Spawned\n";
		p->clientMessage(0xCD5C5CFF, "Welcome");
		return 1; });

	server.getEventPool()->OnPlayerText([](mimp::CPlayer *p, const char *text) -> int
										{
		p->clientMessage(0xFFFFFFFF, mimp::util::strnformat("%s say: %s", strlen(text) + 100, p->getNickName().c_str(), text));
		return 1; });

	server.getEventPool()->OnPlayerCommandText([](mimp::CPlayer *p, const char *cmd) -> int
											   {
		p->clientMessage(0xCD5C5CFF, mimp::util::strnformat("%s command:: %s", 256, p->getNickName().c_str(), cmd));
		int model;
		if(sscanf(cmd, "/create %d", &model)) {
			float x, y, z;
			p->getPos(x, y, z);
			float r = p->getRotation();
			mimp::CVehicle::Create(model, x + 2.000f,y,z,r, -1, -1, 10000, true, false, 0);
			return 1;
		}
		static bool active = 0;
		if(std::string(cmd).find("/checkpoint") != std::string::npos) {
			if(active == 1) {
				p->disableCheckpoint();
				active = 0;
				return 1;
			}

			float x, y, z;
			p->getPos(x, y, z);
			p->setPlayerCheckpoint(x, y, z, 5.0f);
			active = 1;
			return 1;
		}

		char args[1024];
		if(sscanf(cmd, "/getargs %s", args)) {
			p->clientMessage(0xFFFFFFFF, args);
		}
		return 1; });

	server.getEventPool()->OnPlayerUpdate([](mimp::CPlayer *p) -> int
										  { 
			if(p->isPlayerInCheckpoint()) {
				p->clientMessage(0x00FF00FF, "In Checkpoint");
			}
											return 1; });
	// Initialize server
	server.Run(7777);

	while (1)
	{
		server.ProccessTick();
	}

	return 1;
}