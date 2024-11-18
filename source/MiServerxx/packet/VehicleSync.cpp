#include <MiServerxx/packet/PositionSync.hpp>
#include <MiServerxx/packet/VehicleSync.hpp>
#include <MiServerxx/netgame/NetGame.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/core/Core.hpp>

#include <MiRak/PacketEnumerations.h>
#include <MiRak/BitStream.h>
#include <iostream>

using namespace mimp;
using namespace mimp::internal;
using namespace mimp::internal::packet;
extern void UpdatePosition(WORD playerid, float x, float y, float z);
void Packet_VehicleSync(const int uid, Packet* p) {
	RakServerInterface* pRakServer = mimp::internal::server::GetCoreInstance()->getRakServer();
	CPool<CPlayer>* pPlayerPool = internal::server::GetCoreInstance()->GetNetGame()->GetPlayerPool();

	if (p->length < sizeof(INCAR_SYNC_DATA) + 1)
	{
		return;
	}

	RakNet::BitStream bsVehicleSync((unsigned char*)p->data, p->length, false);
	WORD playerId = pRakServer->GetIndexFromPlayerID(p->playerId);

	// clear last data
	mimp::CPlayer* pPlayer = pPlayerPool->GetAt(playerId);
	if (pPlayer == nullptr)
	{
		// Invalid player, usually not connected.
		return;
	}
	memset(pPlayer->getInCarSyncData(), 0, sizeof(INCAR_SYNC_DATA));

	bsVehicleSync.IgnoreBits(8);
	// This guy have bits enough?
	if (bsVehicleSync.GetNumberOfUnreadBits() < sizeof(PASSENGER_SYNC_DATA) * 8)
	{
		// REMOVE HERE
		std::cout << "Invalid vehicle packet.\n";
		return;
	}
	bsVehicleSync.Read((char*)pPlayer->getInCarSyncData(), sizeof(INCAR_SYNC_DATA));

	pPlayer->_setCurrentVehicle(pPlayer->getInCarSyncData()->VehicleID);

	// BROADCAST DATA
	RakNet::BitStream bsInVehicleBC;
	bsInVehicleBC.Write((BYTE)ID_VEHICLE_SYNC);
	bsInVehicleBC.Write(playerId);
	bsInVehicleBC.Write(pPlayer->getInCarSyncData()->VehicleID);

	bsInVehicleBC.Write(pPlayer->getInCarSyncData()->lrAnalog);
	bsInVehicleBC.Write(pPlayer->getInCarSyncData()->udAnalog);
	bsInVehicleBC.Write(pPlayer->getInCarSyncData()->wKeys);

	bsInVehicleBC.WriteNormQuat(
		pPlayer->getInCarSyncData()->fQuaternion[0],
		pPlayer->getInCarSyncData()->fQuaternion[1],
		pPlayer->getInCarSyncData()->fQuaternion[2],
		pPlayer->getInCarSyncData()->fQuaternion[3]);

	bsInVehicleBC.Write(pPlayer->getInCarSyncData()->vecPos[0]);
	bsInVehicleBC.Write(pPlayer->getInCarSyncData()->vecPos[1]);
	bsInVehicleBC.Write(pPlayer->getInCarSyncData()->vecPos[2]);

	bsInVehicleBC.WriteVector(pPlayer->getInCarSyncData()->vecMoveSpeed[0],
		pPlayer->getInCarSyncData()->vecMoveSpeed[1], pPlayer->getInCarSyncData()->vecMoveSpeed[2]);

	WORD wTempVehicleHealh = (WORD)pPlayer->getInCarSyncData()->fCarHealth;
	bsInVehicleBC.Write(wTempVehicleHealh);
	BYTE byteSyncHealthArmour = 0;
	BYTE byteHealth = pPlayer->getInCarSyncData()->bytePlayerHealth;
	BYTE byteArmour = pPlayer->getInCarSyncData()->bytePlayerArmour;
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

	bsInVehicleBC.Write(pPlayer->getInCarSyncData()->byteCurrentWeapon);

	if (pPlayer->getInCarSyncData()->byteSirenOn)
		bsInVehicleBC.Write(true);
	else
		bsInVehicleBC.Write(false);

	if (pPlayer->getInCarSyncData()->byteLandingGearState)
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

	UpdatePosition(playerId, pPlayer->getInCarSyncData()->vecPos[0], pPlayer->getInCarSyncData()->vecPos[1], pPlayer->getInCarSyncData()->vecPos[2]);

	pRakServer->Send(&bsInVehicleBC, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, p->playerId, TRUE);
}