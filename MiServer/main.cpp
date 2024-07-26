#include "MiServer.hpp"
#include <MiRak/RakNetworkFactory.h>
#include <iostream>
#ifdef _WIN32
#pragma comment(lib, "ws2_32")
#endif

int hnd(SOCKET sListen, int iAddrSize, struct sockaddr_in client, char* pBuffer) {
	std::cout << "Query Incomming...\n";
	return 1;
}

int main(void) {
	RakServerInterface* pRakServer = RakNetworkFactory::GetRakServerInterface();
	pRakServer->Start(100, 0, 5, 7777);
	RakNet::RakQuery::setHandler(hnd);
	while (1) {

	}
	return 1;
}