#include <MiServer/packet/BulletSync.hpp>
#include <MiServer/packet/PositionSync.hpp>
#include <MiServer/netgame/NetGame.hpp>
#include <MiServer/server/ServerInstance.hpp>
#include <MiServer/server/Server.hpp>

#include <MiRak/PacketEnumerations.h>
#include <MiRak/BitStream.h>
#include <iostream>

void mimp::internal::packet::BulletSync(Packet *p)
{
	RakServerInterface *pRakServer = mimp::internal::server::GetServerInstance()->getRakServer();
	CPool<CPlayer> *pPlayerPool = internal::server::GetServerInstance()->GetNetGame()->GetPlayerPool();

	if (p->length < sizeof(BULLET_SYNC_DATA) + 1)
	{
		return;
	}

	RakNet::BitStream bsBulletSync((unsigned char *)p->data, p->length, false);
	WORD playerId = pRakServer->GetIndexFromPlayerID(p->playerId);

	mimp::CPlayer *pPlayer = pPlayerPool->GetAt(playerId);
	if (pPlayer == nullptr)
	{
		// Invalid player, usually not connected.
		return;
	}

	memset(pPlayer->m_BulletData, 0, sizeof(BULLET_SYNC_DATA));

	bsBulletSync.IgnoreBits(8);
	// This guy have bits enough?
	if (bsBulletSync.GetNumberOfUnreadBits() < sizeof(BULLET_SYNC_DATA) * 8)
	{
		return;
	}
	bsBulletSync.Read((char *)pPlayer->m_BulletData, sizeof(BULLET_SYNC_DATA));

	// OnPlayerWeaponShot

	bsBulletSync.Reset();

	bsBulletSync.Write((BYTE)ID_BULLET_SYNC);
	bsBulletSync.Write((unsigned short)playerId);
	bsBulletSync.Write((char *)pPlayer->m_BulletData, sizeof(BULLET_SYNC_DATA));

	pRakServer->Send(&bsBulletSync, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, p->playerId, TRUE);
}