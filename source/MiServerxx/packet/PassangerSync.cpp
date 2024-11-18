#include <MiServerxx/packet/BulletSync.hpp>
#include <MiServerxx/packet/PositionSync.hpp>
#include <MiServerxx/packet/PassengerSync.hpp>
#include <MiServerxx/netgame/NetGame.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/core/Core.hpp>
#include <MiRak/PacketEnumerations.h>
#include <MiServerxx/packet/PassengerSync.hpp>
#include <MiRak/BitStream.h>
#include <iostream>

using namespace mimp;
using namespace mimp::internal;
using namespace mimp::internal::packet;
extern void UpdatePosition(WORD playerid, float x, float y, float z);

void Packet_PassengerSync(const int uid, Packet* p) {
	RakServerInterface* pRakServer = mimp::internal::server::GetCoreInstance()->getRakServer();
	CPool<CPlayer>* pPlayerPool = internal::server::GetCoreInstance()->GetNetGame()->GetPlayerPool();

	if (p->length < sizeof(PASSENGER_SYNC_DATA) + 1)
	{
		return;
	}

	RakNet::BitStream bsPassengerSync((unsigned char*)p->data, p->length, false);
	WORD playerId = pRakServer->GetIndexFromPlayerID(p->playerId);

	// clear last data
	mimp::CPlayer* pPlayer = pPlayerPool->GetAt(playerId);
	if (pPlayer == nullptr)
	{
		// Invalid player, usually not connected.
		return;
	}
	memset(pPlayer->getPassengerData(), 0, sizeof(PASSENGER_SYNC_DATA));

	bsPassengerSync.IgnoreBits(8);
	// This guy have bits enough?
	if (bsPassengerSync.GetNumberOfUnreadBits() < sizeof(PASSENGER_SYNC_DATA) * 8)
	{
		return;
	}
	bsPassengerSync.Read((char*)pPlayer->getPassengerData(), sizeof(PASSENGER_SYNC_DATA));

	UpdatePosition(playerId, pPlayer->getPassengerData()->vecPos[0], pPlayer->getPassengerData()->vecPos[1], pPlayer->getPassengerData()->vecPos[2]);
}