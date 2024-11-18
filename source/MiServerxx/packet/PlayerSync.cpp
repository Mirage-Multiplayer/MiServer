#include <MiServerxx/packet/PlayerSync.hpp>
#include <MiServerxx/packet/PositionSync.hpp>
#include <MiServerxx/packet/PassengerSync.hpp>
#include <MiServerxx/netgame/NetGame.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/core/Core.hpp>
#include <MiRak/PacketEnumerations.h>
#include <MiRak/BitStream.h>
#include <MiServerxx/util/euler.hpp>
#include <iostream>

using namespace mimp;
using namespace mimp::internal;
using namespace mimp::internal::packet;
extern void UpdatePosition(WORD playerid, float x, float y, float z);

void Packet_PlayerSync(const int uid, Packet* p) {
	RakServerInterface* pRakServer = mimp::internal::server::GetCoreInstance()->getRakServer();
	CPool<CPlayer>* pPlayerPool = internal::server::GetCoreInstance()->GetNetGame()->GetPlayerPool();

	if (p->length < sizeof(BULLET_SYNC_DATA) + 1)
	{
		return;
	}

	RakNet::BitStream bsPlayerSync((unsigned char*)p->data, p->length, false);
	WORD playerId = pRakServer->GetIndexFromPlayerID(p->playerId);

	// clear last data
	mimp::CPlayer* pPlayer = pPlayerPool->GetAt(playerId);
	if (pPlayer == nullptr)
	{
		// Invalid player, usually not connected.
		return;
	}
	memset(pPlayer->getOnFootSyncData(), 0, sizeof(ONFOOT_SYNC_DATA));

	bsPlayerSync.IgnoreBits(8);
	// This guy have bits enough?
	if (bsPlayerSync.GetNumberOfUnreadBits() < sizeof(ONFOOT_SYNC_DATA) * 8)
	{
		std::cout << "PlayerSync\n";
		return;
	}

	bsPlayerSync.Read((char*)pPlayer->getOnFootSyncData(), sizeof(ONFOOT_SYNC_DATA));

	// BROADCAST DATA
	RakNet::BitStream bsOnFootBC;
	bsOnFootBC.Write((BYTE)ID_PLAYER_SYNC);
	bsOnFootBC.Write((WORD)playerId);

	if (pPlayer->getOnFootSyncData()->lrAnalog)
	{
		bsOnFootBC.Write(true);
		bsOnFootBC.Write(pPlayer->getOnFootSyncData()->lrAnalog);
	}
	else
		bsOnFootBC.Write(false);

	if (pPlayer->getOnFootSyncData()->udAnalog)
	{
		bsOnFootBC.Write(true);
		bsOnFootBC.Write(pPlayer->getOnFootSyncData()->udAnalog);
	}
	else
		bsOnFootBC.Write(false);

	bsOnFootBC.Write(pPlayer->getOnFootSyncData()->wKeys);
	bsOnFootBC.Write(pPlayer->getOnFootSyncData()->vecPos[0]);
	bsOnFootBC.Write(pPlayer->getOnFootSyncData()->vecPos[1]);
	bsOnFootBC.Write(pPlayer->getOnFootSyncData()->vecPos[2]);
	bsOnFootBC.WriteNormQuat(
		pPlayer->getOnFootSyncData()->fQuaternion[0],
		pPlayer->getOnFootSyncData()->fQuaternion[1],
		pPlayer->getOnFootSyncData()->fQuaternion[2],
		pPlayer->getOnFootSyncData()->fQuaternion[3]);

	const float rot = util::GTAQuatResolve(
		pPlayer->getOnFootSyncData()->fQuaternion[1],
		pPlayer->getOnFootSyncData()->fQuaternion[2],
		pPlayer->getOnFootSyncData()->fQuaternion[3], pPlayer->getOnFootSyncData()->fQuaternion[0])
		.z;

	pPlayer->_setRotation(rot);

	BYTE byteSyncHealthArmour = 0;
	BYTE byteHealth = pPlayer->getOnFootSyncData()->byteHealth;
	BYTE byteArmour = pPlayer->getOnFootSyncData()->byteArmour;
	if (byteHealth > 0 && byteHealth < 100)
	{
		byteSyncHealthArmour = ((BYTE)(byteHealth / 7)) << 4;
	}
	else if (byteHealth >= 100)
	{
		byteSyncHealthArmour = 0xF << 4;
	}

	if (byteArmour > 0 && byteArmour < 100)
	{
		byteSyncHealthArmour |= (BYTE)(byteArmour / 7);
	}
	else if (byteArmour >= 100)
	{
		byteSyncHealthArmour |= 0xF;
	}
	bsOnFootBC.Write(byteSyncHealthArmour);
	bsOnFootBC.Write(pPlayer->getOnFootSyncData()->byteCurrentWeapon);
	bsOnFootBC.Write(pPlayer->getOnFootSyncData()->byteSpecialAction);
	bsOnFootBC.WriteVector(pPlayer->getOnFootSyncData()->vecMoveSpeed[0],
		pPlayer->getOnFootSyncData()->vecMoveSpeed[1], pPlayer->getOnFootSyncData()->vecMoveSpeed[2]);

	if (pPlayer->getOnFootSyncData()->wSurfInfo)
	{
		bsOnFootBC.Write(true);
		bsOnFootBC.Write(pPlayer->getOnFootSyncData()->wSurfInfo);
		bsOnFootBC.Write(pPlayer->getOnFootSyncData()->vecSurfOffsets[0]);
		bsOnFootBC.Write(pPlayer->getOnFootSyncData()->vecSurfOffsets[1]);
		bsOnFootBC.Write(pPlayer->getOnFootSyncData()->vecSurfOffsets[2]);
	}
	else
		bsOnFootBC.Write(false);

	if (pPlayer->getOnFootSyncData()->iCurrentAnimationID)
	{
		bsOnFootBC.Write(true);
		bsOnFootBC.Write(pPlayer->getOnFootSyncData()->iCurrentAnimationID);
	}
	else
		bsOnFootBC.Write(false);

	pPlayer->_setCurrentVehicle(0);

	UpdatePosition(playerId, pPlayer->getOnFootSyncData()->vecPos[0], pPlayer->getOnFootSyncData()->vecPos[1], pPlayer->getOnFootSyncData()->vecPos[2]);

	pRakServer->Send(&bsOnFootBC, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, p->playerId, TRUE);
}