#include <MiServerxx/packet/PositionSync.hpp>
#include <MiServerxx/packet/UnoccupiedSync.hpp>
#include <MiServerxx/netgame/NetGame.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/core/Core.hpp>
#include <MiRak/PacketEnumerations.h>
#include <MiRak/BitStream.h>
#include <iostream>

using namespace mimp;
using namespace mimp::internal;
using namespace mimp::internal::packet;
void Packet_UnoccupiedSync(const int uid, Packet* p) {
	RakServerInterface* pRakServer = mimp::internal::server::GetCoreInstance()->getRakServer();
	CPool<CPlayer>* pPlayerPool = internal::server::GetCoreInstance()->GetNetGame()->GetPlayerPool();

	if (p->length < sizeof(UNOCCUPIED_SYNC_DATA) + 1)
	{
		return;
	}

	RakNet::BitStream bsUnocSync((unsigned char*)p->data, p->length, false);
	WORD playerId = pRakServer->GetIndexFromPlayerID(p->playerId);

	// clear last data
	mimp::CPlayer* pPlayer = pPlayerPool->GetAt(playerId);
	if (pPlayer == nullptr)
	{
		// Invalid player, usually not connected.
		return;
	}
	memset(pPlayer->getUnoccupiedData(), 0, sizeof(UNOCCUPIED_SYNC_DATA));

	bsUnocSync.IgnoreBits(8);
	// This guy have bits enough?
	if (bsUnocSync.GetNumberOfUnreadBits() < sizeof(PASSENGER_SYNC_DATA) * 8)
	{
		return;
	}
	bsUnocSync.Read((char*)pPlayer->getUnoccupiedData(), sizeof(UNOCCUPIED_SYNC_DATA));
}