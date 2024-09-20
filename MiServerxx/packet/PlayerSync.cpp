#include <MiServerxx/packet/PlayerSync.hpp>
#include <MiServerxx/packet/PositionSync.hpp>
#include <MiServerxx/packet/PassengerSync.hpp>
#include <MiServerxx/netgame/NetGame.hpp>
#include <MiServerxx/server/ServerInstance.hpp>
#include <MiServerxx/server/Server.hpp>
#include <MiRak/PacketEnumerations.h>
#include <MiRak/BitStream.h>
#include <iostream>

void mimp::internal::packet::PlayerSync(Packet *p)
{
	RakServerInterface *pRakServer = mimp::internal::server::GetServerInstance()->getRakServer();
	CPool<CPlayer> *pPlayerPool = internal::server::GetServerInstance()->GetNetGame()->GetPlayerPool();

	if (p->length < sizeof(BULLET_SYNC_DATA) + 1)
	{
		return;
	}

	RakNet::BitStream bsPlayerSync((unsigned char *)p->data, p->length, false);
	WORD playerId = pRakServer->GetIndexFromPlayerID(p->playerId);

	// clear last data
	mimp::CPlayer *pPlayer = pPlayerPool->GetAt(playerId);
	if (pPlayer == nullptr)
	{
		// Invalid player, usually not connected.
		return;
	}
	memset(pPlayer->m_OnFootSyncData, 0, sizeof(ONFOOT_SYNC_DATA));

	bsPlayerSync.IgnoreBits(8);
	// This guy have bits enough?
	if (bsPlayerSync.GetNumberOfUnreadBits() < sizeof(ONFOOT_SYNC_DATA) * 8)
	{
		std::cout << "PlayerSync\n";
		return;
	}

	bsPlayerSync.Read((char *)pPlayer->m_OnFootSyncData, sizeof(ONFOOT_SYNC_DATA));

	// BROADCAST DATA
	RakNet::BitStream bsOnFootBC;
	bsOnFootBC.Write((BYTE)ID_PLAYER_SYNC);
	bsOnFootBC.Write((WORD)playerId);

	if (pPlayer->m_OnFootSyncData->lrAnalog)
	{
		bsOnFootBC.Write(true);
		bsOnFootBC.Write(pPlayer->m_OnFootSyncData->lrAnalog);
	}
	else
		bsOnFootBC.Write(false);

	if (pPlayer->m_OnFootSyncData->udAnalog)
	{
		bsOnFootBC.Write(true);
		bsOnFootBC.Write(pPlayer->m_OnFootSyncData->udAnalog);
	}
	else
		bsOnFootBC.Write(false);

	bsOnFootBC.Write(pPlayer->m_OnFootSyncData->wKeys);
	bsOnFootBC.Write(pPlayer->m_OnFootSyncData->vecPos[0]);
	bsOnFootBC.Write(pPlayer->m_OnFootSyncData->vecPos[1]);
	bsOnFootBC.Write(pPlayer->m_OnFootSyncData->vecPos[2]);
	bsOnFootBC.WriteNormQuat(
		pPlayer->m_OnFootSyncData->fQuaternion[0],
		pPlayer->m_OnFootSyncData->fQuaternion[1],
		pPlayer->m_OnFootSyncData->fQuaternion[2],
		pPlayer->m_OnFootSyncData->fQuaternion[3]);

	BYTE byteSyncHealthArmour = 0;
	BYTE byteHealth = pPlayer->m_OnFootSyncData->byteHealth;
	BYTE byteArmour = pPlayer->m_OnFootSyncData->byteArmour;
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
	bsOnFootBC.Write(pPlayer->m_OnFootSyncData->byteCurrentWeapon);
	bsOnFootBC.Write(pPlayer->m_OnFootSyncData->byteSpecialAction);
	bsOnFootBC.WriteVector(pPlayer->m_OnFootSyncData->vecMoveSpeed[0],
						   pPlayer->m_OnFootSyncData->vecMoveSpeed[1], pPlayer->m_OnFootSyncData->vecMoveSpeed[2]);

	if (pPlayer->m_OnFootSyncData->wSurfInfo)
	{
		bsOnFootBC.Write(true);
		bsOnFootBC.Write(pPlayer->m_OnFootSyncData->wSurfInfo);
		bsOnFootBC.Write(pPlayer->m_OnFootSyncData->vecSurfOffsets[0]);
		bsOnFootBC.Write(pPlayer->m_OnFootSyncData->vecSurfOffsets[1]);
		bsOnFootBC.Write(pPlayer->m_OnFootSyncData->vecSurfOffsets[2]);
	}
	else
		bsOnFootBC.Write(false);

	if (pPlayer->m_OnFootSyncData->iCurrentAnimationID)
	{
		bsOnFootBC.Write(true);
		bsOnFootBC.Write(pPlayer->m_OnFootSyncData->iCurrentAnimationID);
	}
	else
		bsOnFootBC.Write(false);

	pPlayer->_setCurrentVehicle(0);

	UpdatePosition(playerId, pPlayer->m_OnFootSyncData->vecPos[0], pPlayer->m_OnFootSyncData->vecPos[1], pPlayer->m_OnFootSyncData->vecPos[2]);

	pRakServer->Send(&bsOnFootBC, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, p->playerId, TRUE);
}