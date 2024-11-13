#include <MiServerxx/RPC/RPC.hpp>
#include <MiServerxx/RPC/RPCList.hpp>
#include <MiRak/RakServer.h>
#include <MiRak/BitStream.h>
#include <MiServerxx/core/Core.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/MiServerxx.hpp>
#include <MiServerxx/netgame/NetGame.hpp>
#include <thread>

using namespace mimp::internal;

void SendPlayerPoolToPlayer(WORD playerID)
{
	CPool<mimp::CPlayer>* pPlayerPool = server::GetCoreInstance()->GetNetGame()->GetPlayerPool();
	RakServerInterface* pRakServer = server::GetCoreInstance()->getRakServer();

	// let the player know about all the players in the server
	for (mimp::CPlayer* p : *pPlayerPool)
	{
		if (p == nullptr)
		{
			return;
		}

		if (p->getPlayerId() == playerID)
			continue;

		BYTE byteNameLen = (BYTE)strlen(p->getNickName().c_str());
		RPC::ORPCServerJoin rpc;
		rpc.dColor = 0;
		rpc.isNPC = 0;
		strncpy(rpc.PlayerName, p->getNickName().c_str(), byteNameLen);
		rpc.PlayerNameLength = byteNameLen;
		rpc.wPlayerID = p->getPlayerId();

		server::GetCoreInstance()->SendRPC(playerID, &rpc);

		// In Case of panic!!
		//std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

void SpawnAllVehiclesForPlayer(WORD playerID)
{
	RakServerInterface* pRakServer = server::GetCoreInstance()->getRakServer();
	CPool<mimp::CVehicle>* pVehiclePool = server::GetCoreInstance()->GetNetGame()->GetVehiclePool();
	// spawn all vehicles for this player
	for (mimp::CVehicle* v : *pVehiclePool)
	{
		if (v == nullptr)
		{
			continue;
		}
		float x, y, z;
		v->getPosition(x, y, z);

		RPC::ORPCWorldVehicleAdd worldVehicleAdd;

		worldVehicleAdd.addSiren =v->hasSiren();
		worldVehicleAdd.Angle = v->getRotation();
		worldVehicleAdd.BodyColor1 = v->getColor1();
		worldVehicleAdd.BodyColor2 = v->getColor2();
		worldVehicleAdd.DoorDamageStatus = 0;
		worldVehicleAdd.Health = v->getHealth();
		worldVehicleAdd.interior = v->getInterior();
		worldVehicleAdd.InteriorColor1 = 0;
		worldVehicleAdd.InteriorColor2 = 0;
		worldVehicleAdd.LightDamageStatus = 0;
		worldVehicleAdd.ModelID = v->getModelId();
		memset(worldVehicleAdd.modslot, 0, 14);
		worldVehicleAdd.PaintJob = 0;
		worldVehicleAdd.PanelDamageStatus = 0;
		worldVehicleAdd.tireDamageStatus = 0;
		worldVehicleAdd.wVehicleID = v->getId();
		worldVehicleAdd.X = x;
		worldVehicleAdd.Y = y;
		worldVehicleAdd.Z = z;
		server::GetCoreInstance()->BroadcastRPC(&worldVehicleAdd);

		// In Case of panic!!
		//std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

void IRPCFunc_ClientJoin(RPCParameters* rpcParams) {
	mimp::ServerConfig cfg = server::GetCoreInstance()->getConfig();
	RakServerInterface* pRakServer = server::GetCoreInstance()->getRakServer();
	CPool<mimp::CPlayer>* pPlayerPool = server::GetCoreInstance()->GetNetGame()->GetPlayerPool();

	char* Data = reinterpret_cast<char*>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;
	PlayerID sender = rpcParams->sender;

	RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);
	RakNet::BitStream bsReject;

	char szNickName[32], pszAuthBullshit[44];
	int iVersion;
	unsigned int uiChallengeResponse;
	BYTE byteMod, byteNameLen, byteAuthBSLen;
	WORD playerID = pRakServer->GetIndexFromPlayerID(sender);
	BYTE byteRejectReason;

	bsData.Read(iVersion);
	bsData.Read(byteMod);
	bsData.Read(byteNameLen);
	bsData.Read(szNickName, byteNameLen);
	szNickName[byteNameLen] = 0;
	bsData.Read(uiChallengeResponse);
	bsData.Read(byteAuthBSLen);
	bsData.Read(pszAuthBullshit, byteAuthBSLen);
	pszAuthBullshit[byteAuthBSLen] = 0;

	PlayerID MyPlayerID = pRakServer->GetPlayerIDFromIndex(playerID);
	in_addr in;
	if (UNASSIGNED_PLAYER_ID == MyPlayerID)
	{
		in.s_addr = sender.binaryAddress;
		printf("Detected possible bot from (%s)", inet_ntoa(in));
		pRakServer->Kick(MyPlayerID);
		return;
	}

	if (!pRakServer->IsActivePlayerID(sender) || playerID > pPlayerPool->GetMax())
	{
		RPC::ORPCConnectionRejected rpc;
		
		byteRejectReason = REJECT_REASON_BAD_PLAYERID;
		bsReject.Write(byteRejectReason);
		int uid = rpc.GetUID();
		pRakServer->RPC(&uid, &bsReject, HIGH_PRIORITY, RELIABLE,
			0, sender, FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
		pRakServer->Kick(sender);
		return;
	}

	if (iVersion != NETGAME_VERSION || RakNet::RakEncr::m_srvChallenge != (uiChallengeResponse ^ NETGAME_VERSION))
	{
		RPC::ORPCConnectionRejected rpc;
		byteRejectReason = REJECT_REASON_BAD_VERSION;
		bsReject.Write(byteRejectReason);
		int uid = rpc.GetUID();
		pRakServer->RPC(&uid, &bsReject, HIGH_PRIORITY, RELIABLE,
			0, sender, FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
		pRakServer->Kick(sender);
		return;
	}

	pPlayerPool->InsertAt(playerID, new mimp::CPlayer(rpcParams->sender, playerID, szNickName));

	RPC::ORPCInitGame rpc;
	rpc.bAllowWeapons = cfg.allowedWeapons;
	rpc.bDisableEnterExits = cfg.disableEnterExits;
	rpc.bInstagib = cfg.instagib;
	rpc.bLanMode = cfg.lanMode;
	rpc.bLimitGlobalChatRadius = cfg.limitGlobalChatRadius;
	rpc.bManualVehEngineAndLights = cfg.manualVehicleEngineAndLight;
	rpc.fNameTagDistance = cfg.nameTagDrawDistance;
	rpc.dWeaponRate = cfg.netModeFiringSendRate;
	rpc.dInCarRate = cfg.netModeNormalIncarSendRate;
	rpc.dOnfootRate = cfg.netModeNormalOnfootSendRate;
	rpc.dMultiplier = cfg.netModeSendMultiplier;
	rpc.dShowPlayerMarkers = cfg.showPlayerMarkers;
	rpc.bShowNameTags = cfg.showPlayerTags;
	rpc.bStuntBonus = cfg.stuntBonus;
	rpc.fGravity = cfg.gravity;
	rpc.fGlobalChatRadius = cfg.globalChatRadius;
	rpc.dDeathDropMoney = cfg.deathDropMoney;
	rpc.dSpawnsAvailable = cfg.spawnsAvailable;
	rpc.bNameTagLOS = cfg.nameTagLOS;
	rpc.bZoneNames = cfg.zoneNames;
	rpc.bUseCJWalk = cfg.useCJWalk;
	rpc.bWeather = cfg.weather;
	rpc.bWorldTime = cfg.worldTime;
	rpc.dLagCompMode = cfg.lagCompensation;
	rpc.dVehicleFriendlyFire = 0;

	int hostnamelen = server::GetCoreInstance()->getInfo().hostname.length();
	strncpy(rpc.HostName, server::GetCoreInstance()->getInfo().hostname.c_str(), hostnamelen);
	rpc.length = hostnamelen;

	server::GetCoreInstance()->SendRPC(playerID, &rpc);

	// InitGameForPlayer(playerID);
	SendPlayerPoolToPlayer(playerID);
	SpawnAllVehiclesForPlayer(playerID);

	MIMP_GET_EVENT(PLAYERCONNECT, server::GetCoreInstance()
		->getEventPool())
		PLAYERCONNECT->Emit(pPlayerPool->GetAt(playerID));
}