#include <MiServerxx/packet/PositionSync.hpp>
#include <MiServerxx/packet/VehicleSync.hpp>
#include <MiServerxx/netgame/NetGame.hpp>
#include <MiServerxx/server/ServerInstance.hpp>
#include <MiServerxx/server/Server.hpp>

#include <MiRak/PacketEnumerations.h>
#include <MiRak/BitStream.h>
#include <iostream>

void mimp::internal::packet::VehicleSync(Packet *p)
{
	RakServerInterface *pRakServer = mimp::internal::server::GetServerInstance()->getRakServer();
	CPool<CPlayer> *pPlayerPool = internal::server::GetServerInstance()->GetNetGame()->GetPlayerPool();

	if (p->length < sizeof(INCAR_SYNC_DATA) + 1)
	{
		return;
	}

	RakNet::BitStream bsVehicleSync((unsigned char *)p->data, p->length, false);
	WORD playerId = pRakServer->GetIndexFromPlayerID(p->playerId);

	// clear last data
	mimp::CPlayer *pPlayer = pPlayerPool->GetAt(playerId);
	if (pPlayer == nullptr)
	{
		// Invalid player, usually not connected.
		return;
	}
	memset(pPlayer->m_InCarSyncData, 0, sizeof(INCAR_SYNC_DATA));

	bsVehicleSync.IgnoreBits(8);
	// This guy have bits enough?
	if (bsVehicleSync.GetNumberOfUnreadBits() < sizeof(PASSENGER_SYNC_DATA) * 8)
	{
		// REMOVE HERE
		std::cout << "Invalid vehicle packet.\n";
		return;
	}
	bsVehicleSync.Read((char *)pPlayer->m_InCarSyncData, sizeof(INCAR_SYNC_DATA));

	pPlayer->_setCurrentVehicle(pPlayer->m_InCarSyncData->VehicleID);

	// BROADCAST DATA
	RakNet::BitStream bsInVehicleBC;
	bsInVehicleBC.Write((BYTE)ID_VEHICLE_SYNC);
	bsInVehicleBC.Write(playerId);
	bsInVehicleBC.Write(pPlayer->m_InCarSyncData->VehicleID);

	bsInVehicleBC.Write(pPlayer->m_InCarSyncData->lrAnalog);
	bsInVehicleBC.Write(pPlayer->m_InCarSyncData->udAnalog);
	bsInVehicleBC.Write(pPlayer->m_InCarSyncData->wKeys);

	bsInVehicleBC.WriteNormQuat(
		pPlayer->m_InCarSyncData->fQuaternion[0],
		pPlayer->m_InCarSyncData->fQuaternion[1],
		pPlayer->m_InCarSyncData->fQuaternion[2],
		pPlayer->m_InCarSyncData->fQuaternion[3]);

	bsInVehicleBC.Write(pPlayer->m_InCarSyncData->vecPos[0]);
	bsInVehicleBC.Write(pPlayer->m_InCarSyncData->vecPos[1]);
	bsInVehicleBC.Write(pPlayer->m_InCarSyncData->vecPos[2]);

	bsInVehicleBC.WriteVector(pPlayer->m_InCarSyncData->vecMoveSpeed[0],
							  pPlayer->m_InCarSyncData->vecMoveSpeed[1], pPlayer->m_InCarSyncData->vecMoveSpeed[2]);

	WORD wTempVehicleHealh = (WORD)pPlayer->m_InCarSyncData->fCarHealth;
	bsInVehicleBC.Write(wTempVehicleHealh);
	BYTE byteSyncHealthArmour = 0;
	BYTE byteHealth = pPlayer->m_InCarSyncData->bytePlayerHealth;
	BYTE byteArmour = pPlayer->m_InCarSyncData->bytePlayerArmour;
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
	bsInVehicleBC.Write(byteSyncHealthArmour);

	bsInVehicleBC.Write(pPlayer->m_InCarSyncData->byteCurrentWeapon);

	if (pPlayer->m_InCarSyncData->byteSirenOn)
		bsInVehicleBC.Write(true);
	else
		bsInVehicleBC.Write(false);

	if (pPlayer->m_InCarSyncData->byteLandingGearState)
		bsInVehicleBC.Write(true);
	else
		bsInVehicleBC.Write(false);

	// HYDRA THRUST ANGLE AND TRAILER ID
	bsInVehicleBC.Write(false);
	bsInVehicleBC.Write(false);

	DWORD dwTrailerID_or_ThrustAngle = 0;
	bsInVehicleBC.Write(dwTrailerID_or_ThrustAngle);

	// TRAIN SPECIAL
	bsInVehicleBC.Write(false);
	/*WORD wSpeed;
	bsSync.ReadCompressed(bTrain);
	if(bTrain)
	{
		bsSync.Read(wSpeed);
		playerInfo[playerId].incarData.fTrainSpeed = (float)wSpeed;
	}*/

	UpdatePosition(playerId, pPlayer->m_InCarSyncData->vecPos[0], pPlayer->m_InCarSyncData->vecPos[1], pPlayer->m_InCarSyncData->vecPos[2]);

	pRakServer->Send(&bsInVehicleBC, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, p->playerId, TRUE);
}