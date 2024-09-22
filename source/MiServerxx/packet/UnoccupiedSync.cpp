#include <MiServerxx/packet/PositionSync.hpp>
#include <MiServerxx/packet/UnoccupiedSync.hpp>
#include <MiServerxx/netgame/NetGame.hpp>
#include <MiServerxx/server/ServerInstance.hpp>
#include <MiServerxx/server/Server.hpp>
#include <MiRak/PacketEnumerations.h>
#include <MiRak/BitStream.h>
#include <iostream>

void mimp::internal::packet::UnoccupiedSync(Packet *p)
{
	RakServerInterface *pRakServer = mimp::internal::server::GetServerInstance()->getRakServer();
	CPool<CPlayer> *pPlayerPool = internal::server::GetServerInstance()->GetNetGame()->GetPlayerPool();

	if (p->length < sizeof(UNOCCUPIED_SYNC_DATA) + 1)
	{
		return;
	}

	RakNet::BitStream bsUnocSync((unsigned char *)p->data, p->length, false);
	WORD playerId = pRakServer->GetIndexFromPlayerID(p->playerId);

	// clear last data
	mimp::CPlayer *pPlayer = pPlayerPool->GetAt(playerId);
	if (pPlayer == nullptr)
	{
		// Invalid player, usually not connected.
		return;
	}
	memset(pPlayer->m_UnoccupiedData, 0, sizeof(UNOCCUPIED_SYNC_DATA));

	bsUnocSync.IgnoreBits(8);
	// This guy have bits enough?
	if (bsUnocSync.GetNumberOfUnreadBits() < sizeof(PASSENGER_SYNC_DATA) * 8)
	{
		return;
	}
	bsUnocSync.Read((char *)pPlayer->m_UnoccupiedData, sizeof(UNOCCUPIED_SYNC_DATA));
}