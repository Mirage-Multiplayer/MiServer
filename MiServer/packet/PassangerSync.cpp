#include <MiServer/packet/BulletSync.hpp>
#include <MiServer/packet/PositionSync.hpp>
#include <MiServer/packet/PassengerSync.hpp>
#include <MiServer/player/PlayerTypes.hpp>
#include <MiServer/player/PlayerPool.hpp>
#include <MiServer/player/Player.hpp>
#include <MiServer/server/ServerInstance.hpp>
#include <MiServer/server/Server.hpp>
#include <MiRak/PacketEnumerations.h>
#include <MiRak/BitStream.h>
#include <iostream>

void mimp::internal::packet::PassengerSync(Packet *p)
{
	RakServerInterface *pRakServer = mimp::internal::server::GetServerInstance()->getRakServer();
	mimp::internal::player::PlayerPool *pPlayerPool = mimp::internal::server::GetServerInstance()->getPlayerPool();

	if (p->length < sizeof(PASSENGER_SYNC_DATA) + 1)
	{
		return;
	}

	RakNet::BitStream bsPassengerSync((unsigned char *)p->data, p->length, false);
	PLAYERID playerId = pRakServer->GetIndexFromPlayerID(p->playerId);

	// clear last data
	mimp::Player *pPlayer = pPlayerPool->Get(playerId);
	if (pPlayer == nullptr)
	{
		// Invalid player, usually not connected.
		return;
	}
	memset(pPlayer->m_PassengerData, 0, sizeof(PASSENGER_SYNC_DATA));

	bsPassengerSync.IgnoreBits(8);
	// This guy have bits enough?
	if (bsPassengerSync.GetNumberOfUnreadBits() < sizeof(PASSENGER_SYNC_DATA) * 8)
	{
		return;
	}
	bsPassengerSync.Read((char *)pPlayer->m_PassengerData, sizeof(PASSENGER_SYNC_DATA));

	UpdatePosition(playerId, pPlayer->m_PassengerData->vecPos[0], pPlayer->m_PassengerData->vecPos[1], pPlayer->m_PassengerData->vecPos[2]);
}