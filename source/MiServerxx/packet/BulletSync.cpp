#include <MiServerxx/packet/BulletSync.hpp>
#include <MiServerxx/packet/PositionSync.hpp>
#include <MiServerxx/netgame/NetGame.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/core/Core.hpp>

#include <MiRak/PacketEnumerations.h>
#include <MiRak/BitStream.h>
#include <iostream>

using namespace mimp;
using namespace mimp::internal;
using namespace mimp::internal::packet;

void Packet_BulletSync(const int uid, Packet* p)
{
	RakServerInterface* pRakServer = mimp::internal::server::GetCoreInstance()->getRakServer();
	CPool<CPlayer>* pPlayerPool = internal::server::GetCoreInstance()->GetNetGame()->GetPlayerPool();

	if (p->length < sizeof(BULLET_SYNC_DATA) + 1)
	{
		return;
	}

	RakNet::BitStream bsBulletSync((unsigned char*)p->data, p->length, false);
	WORD playerId = pRakServer->GetIndexFromPlayerID(p->playerId);

	mimp::CPlayer* pPlayer = pPlayerPool->GetAt(playerId);
	if (pPlayer == nullptr)
	{
		// Invalid player, usually not connected.
		return;
	}

	memset(pPlayer->getBulletData(), 0, sizeof(BULLET_SYNC_DATA));

	bsBulletSync.IgnoreBits(8);
	// This guy have bits enough?
	if (bsBulletSync.GetNumberOfUnreadBits() < sizeof(BULLET_SYNC_DATA) * 8)
	{
		return;
	}
	bsBulletSync.Read((char*)pPlayer->getBulletData(), sizeof(BULLET_SYNC_DATA));

	// OnPlayerWeaponShot

	bsBulletSync.Reset();

	RakNet::BitStream bsOutgoing;
	bsOutgoing.Write((BYTE)ID_BULLET_SYNC);
	bsOutgoing.Write((unsigned short)playerId);
	bsOutgoing.Write((char*)pPlayer->getBulletData(), sizeof(BULLET_SYNC_DATA));

	pRakServer->Send(&bsOutgoing, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, p->playerId, TRUE);
}
