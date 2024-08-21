#include <MiServer/packet/PositionSync.hpp>
#include <MiServer/packet/UnoccupiedSync.hpp>
#include <MiServer/player/PlayerTypes.hpp>
#include <MiServer/player/PlayerPool.hpp>
#include <MiServer/player/Player.hpp>
#include <MiServer/server/ServerInstance.hpp>
#include <MiServer/server/Server.hpp>
#include <MiRak/PacketEnumerations.h>
#include <MiRak/BitStream.h>
#include <iostream>

void mimp::internal::packet::UnoccupiedSync(Packet *p)
{
	RakServerInterface *pRakServer = mimp::internal::server::GetServerInstance()->getRakServer();
	mimp::internal::player::PlayerPool *pPlayerPool = mimp::internal::server::GetServerInstance()->getPlayerPool();

	if (p->length < sizeof(UNOCCUPIED_SYNC_DATA) + 1)
	{
		return;
	}

	RakNet::BitStream bsUnocSync((unsigned char *)p->data, p->length, false);
	PLAYERID playerId = pRakServer->GetIndexFromPlayerID(p->playerId);

	// clear last data
	mimp::Player *pPlayer = pPlayerPool->Get(playerId);
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