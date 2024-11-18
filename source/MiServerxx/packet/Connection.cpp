#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/core/Core.hpp>
#include <MiServerxx/netgame/NetGame.hpp>

void Packet_DisconnectionNotification(const int uid, Packet* p) {
	mimp::CCore* pCore = mimp::internal::server::GetCoreInstance();
	WORD playerID = p->playerIndex;
	pCore->GetNetGame()->GetPlayerPool()->DeleteAt(playerID);
}

void Packet_NewIncomingConnection(const int uid, Packet* p) {

}

void Packet_ConnectionLost(const int uid, Packet* p) {
	mimp::CCore* pCore = mimp::internal::server::GetCoreInstance();
	WORD playerID = p->playerIndex;
	pCore->GetNetGame()->GetPlayerPool()->DeleteAt(playerID);
}