#include <MiRak/BitStream.h>
#include <MiRak/RakEncr.h>
#include <string>
#include "server/Server.hpp"
#include "server/ServerInstance.hpp"
#include "MiServer.hpp"
#include "types.h"
#include "RPC/RPCList.hpp"
#include "RPC/RPC.hpp"
#include "packet/SyncData.hpp"
#include "player/defines.hpp"
#include "player/PlayerTypes.hpp"
#include "vehicle/Vehicle.hpp"
#include "vehicle/VehiclePool.hpp"
#include "vehicle/defines.hpp"

namespace mimp {
	namespace internal {
		namespace RPC {
			float m_fGravity = 0.008f;

			int iLagCompensation = 1;

			void InitGameForPlayer(PLAYERID playerID)
			{
				mimp::Server* svr = mimp::internal::server::GetServerInstance();
				
				// TODO: Modify server config
				RakNet::BitStream bsInitGame;
				bsInitGame.WriteCompressed((bool)1); // m_bZoneNames
				bsInitGame.WriteCompressed((bool)1); // m_bUseCJWalk
				bsInitGame.WriteCompressed((bool)1); // m_bAllowWeapons
				bsInitGame.WriteCompressed((bool)0); // m_bLimitGlobalChatRadius
				bsInitGame.Write((float)200.00f); // m_fGlobalChatRadius
				bsInitGame.WriteCompressed((bool)0); // bStuntBonus
				bsInitGame.Write((float)70.0f); // m_fNameTagDrawDistance
				bsInitGame.WriteCompressed((bool)0); // m_bDisableEnterExits
				bsInitGame.WriteCompressed((bool)1); // m_bNameTagLOS
				bsInitGame.WriteCompressed((bool)0); // m_bManualVehicleEngineAndLight
				bsInitGame.Write((int)1); // m_iSpawnsAvailable
				bsInitGame.Write(playerID); // MyPlayerID
				bsInitGame.WriteCompressed((bool)1); // m_bShowPlayerTags
				bsInitGame.Write((int)1); // m_iShowPlayerMarkers
				bsInitGame.Write((BYTE)12); // m_byteWorldTime
				bsInitGame.Write((BYTE)10); // m_byteWeather
				bsInitGame.Write((float)m_fGravity); // m_fGravity
				bsInitGame.WriteCompressed((bool)0); // bLanMode
				bsInitGame.Write((int)0); // m_iDeathDropMoney
				bsInitGame.WriteCompressed((bool)0); // m_bInstagib

				bsInitGame.Write((int)40); // iNetModeNormalOnfootSendRate
				bsInitGame.Write((int)40); // iNetModeNormalIncarSendRate
				bsInitGame.Write((int)40); // iNetModeFiringSendRate
				bsInitGame.Write((int)10); // iNetModeSendMultiplier

				bsInitGame.Write((BYTE)iLagCompensation); // m_bLagCompensation

				bsInitGame.Write((BYTE)0); // unknown
				bsInitGame.Write((BYTE)0); // unknown
				bsInitGame.Write((BYTE)0); // unknown

				BYTE bServerNameLen = (BYTE)strlen(svr->getInfo().hostname.c_str());
				bsInitGame.Write(bServerNameLen);
				bsInitGame.Write(svr->getInfo().hostname.c_str(), bServerNameLen);

				BYTE vehModels[212];
				memset(vehModels, 1, 212);
				bsInitGame.Write((char*)&vehModels, 212);

				svr->getRakServer()->RPC(&RPC_InitGame, &bsInitGame, HIGH_PRIORITY, RELIABLE,
					0, svr->getRakServer()->GetPlayerIDFromIndex(playerID), FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
			}

			void SendPlayerPoolToPlayer(PLAYERID playerID)
			{
				mimp::Server* svr = mimp::internal::server::GetServerInstance();
				mimp::internal::player::PlayerPool* pPlayerPool = svr->getPlayerPool();
				RakServerInterface* pRakServer = svr->getRakServer();
				// let the player know about all the players in the server
				for (PLAYERID p = 0; p < MAX_PLAYERS; p++)
				{
					if (!pPlayerPool->IsPlayerConnected(p))
						continue;

					if (p == playerID)
						continue;

					BYTE byteNameLen = (BYTE)strlen(pPlayerPool->Get(p)->getNickName().c_str());
					RakNet::BitStream bs;
					bs.Reset();
					bs.Write(p);
					bs.Write((int)1);
					bs.Write((BYTE)0);
					bs.Write(byteNameLen);
					bs.Write(pPlayerPool->Get(p)->getNickName().c_str(), byteNameLen);
					pRakServer->RPC(&RPC_ServerJoin, &bs, HIGH_PRIORITY, RELIABLE,
						0, pRakServer->GetPlayerIDFromIndex(playerID), FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);

					Sleep(5); // well, shit.
				}
			}

			void SpawnAllVehiclesForPlayer(PLAYERID playerID)
			{
				RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
				internal::vehicle::VehiclePool* pVehiclePool = internal::server::GetServerInstance()->getVehiclePool();
				// spawn all vehicles for this player
				for (VEHICLEID v = 0; v < MAX_VEHICLES; v++)
				{
					if (!pVehiclePool->IsValidVehicle(v)) {
						continue;
					}
					
					mimp::Vehicle veh = *pVehiclePool->Get(v);

					internal::packet::NEW_VEHICLE newVeh;
					memset(&newVeh, 0, sizeof(internal::packet::NEW_VEHICLE));
					newVeh.VehicleId = v;
					newVeh.iVehicleType = veh.m_modelId;
					newVeh.vecPos[0] = veh.m_pos[0];
					newVeh.vecPos[1] = veh.m_pos[1];
					newVeh.vecPos[2] = veh.m_pos[2];
					newVeh.fRotation = veh.m_rotation;
					newVeh.fHealth = 1000.00f;
					newVeh.byteInterior = 0;
					newVeh.dwDoorDamageStatus = 0;
					newVeh.dwPanelDamageStatus = 0;
					newVeh.byteLightDamageStatus = 0;

					RakNet::BitStream bs;
					bs.Write((const char*)&newVeh, sizeof(internal::packet::NEW_VEHICLE));
					pRakServer->RPC(&RPC_WorldVehicleAdd, &bs, HIGH_PRIORITY, RELIABLE,
						0, pRakServer->GetPlayerIDFromIndex(playerID), FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);

					Sleep(5); // well, shit.
				}
			}

			void ClientJoin(RPCParameters* rpcParams)
			{
				RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
				internal::player::PlayerPool* pPlayerPool = internal::server::GetServerInstance()->getPlayerPool();

				PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
				int iBitLength = rpcParams->numberOfBitsOfData;
				PlayerID sender = rpcParams->sender;

				RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);
				RakNet::BitStream bsReject;

				char szNickName[32], pszAuthBullshit[44];
				int iVersion;
				unsigned int uiChallengeResponse;
				BYTE byteMod, byteNameLen, byteAuthBSLen;
				PLAYERID playerID = pRakServer->GetIndexFromPlayerID(sender);
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

				if (!pRakServer->IsActivePlayerID(sender) || playerID > MAX_PLAYERS)
				{
					byteRejectReason = REJECT_REASON_BAD_PLAYERID;
					bsReject.Write(byteRejectReason);
					pRakServer->RPC(&RPC_ConnectionRejected, &bsReject, HIGH_PRIORITY, RELIABLE,
						0, sender, FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
					pRakServer->Kick(sender);
					return;
				}

				if (iVersion != NETGAME_VERSION || RakNet::RakEncr::m_srvChallenge != (uiChallengeResponse ^ NETGAME_VERSION))
				{
					byteRejectReason = REJECT_REASON_BAD_VERSION;
					bsReject.Write(byteRejectReason);
					pRakServer->RPC(&RPC_ConnectionRejected, &bsReject, HIGH_PRIORITY, RELIABLE,
						0, sender, FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
					pRakServer->Kick(sender);
					return;
				}

				pPlayerPool->Add(new mimp::Player(rpcParams->sender, playerID, szNickName));
				

				InitGameForPlayer(playerID);
				SendPlayerPoolToPlayer(playerID);
				SpawnAllVehiclesForPlayer(playerID);

				// OnPlayerConnect
			}

			void RequestClass(RPCParameters* rpcParams)
			{
				PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
				int iBitLength = rpcParams->numberOfBitsOfData;

				RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);

				int iClass;
				bsData.Read(iClass);

				mimp::internal::packet::PLAYER_SPAWN_INFO psInfo;
				memset(&psInfo, 0, sizeof(psInfo));
				psInfo.byteTeam = 0xFF;
				psInfo.iSkin = 33;
				psInfo.vecPos[0] = 389.8672f;
				psInfo.vecPos[1] = 2543.0046f;
				psInfo.vecPos[2] = 16.5391f;
				psInfo.fRotation = 90.0f;
				psInfo.iSpawnWeapons[0] = 38;
				psInfo.iSpawnWeaponsAmmo[0] = 69;

				// OnPlayerRequestClass
				

				RakNet::BitStream bsReply;
				bsReply.Write((BYTE)1);
				bsReply.Write((char*)&psInfo, sizeof(psInfo));
				RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
				pRakServer->RPC(&RPC_RequestClass, &bsReply, HIGH_PRIORITY, RELIABLE,
					0, rpcParams->sender, FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
			}

			void RequestSpawn(RPCParameters* rpcParams)
			{
				RakNet::BitStream bsReply;

				bsReply.Write((BYTE)2);
				RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
				pRakServer->RPC(&RPC_RequestSpawn, &bsReply, HIGH_PRIORITY, RELIABLE,
					0, rpcParams->sender, FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
			}

			void Spawn(RPCParameters* rpcParams)
			{
				RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
				PLAYERID playerId = (PLAYERID)pRakServer->GetIndexFromPlayerID(rpcParams->sender);
				BYTE byteFightingStyle = 4;
				BYTE byteTeam = -1;
				int iSkin = 0;
				float vecPos[3] = { 389.8672f, 2543.0046f, 16.5391f };
				float fRotation = 90.0f;
				DWORD dwColor = -1;

				// OnPlayerSpawn

				RakNet::BitStream bsData;
				bsData.Write(playerId);
				bsData.Write(byteTeam);
				bsData.Write(iSkin);
				bsData.Write(vecPos[0]);
				bsData.Write(vecPos[1]);
				bsData.Write(vecPos[2]);
				bsData.Write(fRotation);
				bsData.Write(dwColor);
				bsData.Write(byteFightingStyle);
				pRakServer->RPC(&RPC_WorldPlayerAdd, &bsData, HIGH_PRIORITY, RELIABLE_ORDERED,
					0, pRakServer->GetPlayerIDFromIndex(playerId), TRUE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
			}

			void Chat(RPCParameters* rpcParams)
			{
				RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();

				PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
				int iBitLength = rpcParams->numberOfBitsOfData;
				RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);

				PLAYERID playerId = (PLAYERID)pRakServer->GetIndexFromPlayerID(rpcParams->sender);
				char szText[256];
				BYTE byteTextLen;

				memset(szText, 0, 256);

				bsData.Read(byteTextLen);
				bsData.Read((char*)szText, byteTextLen);
				szText[byteTextLen] = '\0';

				// OnPlayerMessage

			}

			void UpdateScoresPingsIPs(RPCParameters* rpcParams)
			{
				RakNet::BitStream bsUpdate;
				RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
				internal::player::PlayerPool* pPlayerPool = internal::server::GetServerInstance()->getPlayerPool();
				for (PLAYERID i = 0; i < MAX_PLAYERS; i++)
				{
					if (pPlayerPool->IsPlayerConnected(i))
					{
						pPlayerPool->Get(i)->setPing(pRakServer->GetLastPing(pPlayerPool->Get(i)->getRakPlayerId()));

						bsUpdate.Write(i);
						bsUpdate.Write(pPlayerPool->Get(i)->getScore());
						bsUpdate.Write(pPlayerPool->Get(i)->getPing());
					}
				}

				pRakServer->RPC(&RPC_UpdateScoresPingsIPs, &bsUpdate, HIGH_PRIORITY, RELIABLE, 0,
					rpcParams->sender, FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
			}

			void DamageVehicle(RPCParameters* rpcParams)
			{
				RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
				internal::player::PlayerPool* pPlayerPool = internal::server::GetServerInstance()->getPlayerPool();

				PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
				int iBitLength = rpcParams->numberOfBitsOfData;
				PlayerID sender = rpcParams->sender;

				RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);
				PLAYERID playerID = pRakServer->GetIndexFromPlayerID(sender);

				if (!pPlayerPool->IsPlayerConnected(playerID))
					return;

				VEHICLEID vehID;
				uint32_t vehPanels;
				uint32_t vehDoors;
				uint8_t vehLights;
				uint8_t vehTires;

				bsData.Read(vehID);
				bsData.Read(vehPanels);
				bsData.Read(vehDoors);
				bsData.Read(vehLights);
				bsData.Read(vehTires);

				if (vehID == (VEHICLEID)-1)
				{
					//SendClientMessage(playerID, -1, "You are sending an invalid vehicle ID. Unlike kye, we wont kick you :)");
					return;
				}

				// OnPlayerDamageVehicle

				RakNet::BitStream bsDamage;

				bsDamage.Write(vehID);
				bsDamage.Write(vehPanels);
				bsDamage.Write(vehDoors);
				bsDamage.Write(vehLights);
				bsDamage.Write(vehTires);

				pRakServer->RPC(&RPC_DamageVehicle, &bsDamage, HIGH_PRIORITY, RELIABLE_ORDERED, 0, sender, TRUE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
			}

			void EnterVehicle(RPCParameters* rpcParams)
			{
				RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
				mimp::internal::player::PlayerPool* pPlayerPool = internal::server::GetServerInstance()->getPlayerPool();

				PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
				int iBitLength = rpcParams->numberOfBitsOfData;
				PlayerID sender = rpcParams->sender;

				RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);
				PLAYERID playerID = pRakServer->GetIndexFromPlayerID(sender);

				if (!pPlayerPool->IsPlayerConnected(playerID))
					return;

				VEHICLEID VehicleID = 0;
				BYTE bytePassenger = 0;

				bsData.Read(VehicleID);
				bsData.Read(bytePassenger);

				if (VehicleID == (VEHICLEID)-1)
				{
					//SendClientMessage(playerID, -1, "You are sending an invalid vehicle ID. Unlike kye, we wont kick you :)");
					return;
				}

				// OnPlayerEnterVehicle
				
				mimp::Player* pPlayer = pPlayerPool->Get(playerID);
				pPlayer->getInCarSyncData()->VehicleID = VehicleID;

				RakNet::BitStream bsVehicle;
				bsVehicle.Write(playerID);
				bsVehicle.Write(VehicleID);
				bsVehicle.Write(bytePassenger);
				pRakServer->RPC(&RPC_EnterVehicle, &bsVehicle, HIGH_PRIORITY, RELIABLE_ORDERED,
					0, sender, TRUE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
			}


			void ExitVehicle(RPCParameters* rpcParams)
			{
				RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
				mimp::internal::player::PlayerPool* pPlayerPool = internal::server::GetServerInstance()->getPlayerPool();

				PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
				int iBitLength = rpcParams->numberOfBitsOfData;
				PlayerID sender = rpcParams->sender;

				RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);
				PLAYERID playerID = pRakServer->GetIndexFromPlayerID(sender);

				if (!pPlayerPool->IsPlayerConnected(playerID))
					return;

				VEHICLEID VehicleID;
				bsData.Read(VehicleID);

				if (VehicleID == (VEHICLEID)-1)
				{
					//SendClientMessage(playerID, -1, "You are sending an invalid vehicle ID. Unlike kye, we wont kick you :)");
					return;
				}

				// OnPlayerExitVehicle

				mimp::Player* pPlayer = pPlayerPool->Get(playerID);
				pPlayer->getInCarSyncData()->VehicleID = -1;

				RakNet::BitStream bsVehicle;
				bsVehicle.Write(playerID);
				bsVehicle.Write(VehicleID);
				pRakServer->RPC(&RPC_ExitVehicle, &bsVehicle, HIGH_PRIORITY, RELIABLE_ORDERED,
					0, sender, TRUE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
			}

			void ServerCommand(RPCParameters* rpcParams)
			{
				RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
				mimp::internal::player::PlayerPool* pPlayerPool = internal::server::GetServerInstance()->getPlayerPool();

				PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
				int iBitLength = rpcParams->numberOfBitsOfData;
				PlayerID sender = rpcParams->sender;

				RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);
				PLAYERID playerID = pRakServer->GetIndexFromPlayerID(sender);

				if (!pPlayerPool->IsPlayerConnected(playerID))
					return;

				char szCommand[256];
				int szCommandLength = strlen(szCommand);

				bsData.Read(szCommandLength);
				bsData.Read(szCommand, szCommandLength);
				szCommand[szCommandLength] = '\0';

				// OnPlayerCommand
				
			}

			void Death(RPCParameters* rpcParams)
			{
				RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
				mimp::internal::player::PlayerPool* pPlayerPool = internal::server::GetServerInstance()->getPlayerPool();

				PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
				int iBitLength = rpcParams->numberOfBitsOfData;
				PlayerID sender = rpcParams->sender;

				RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);
				PLAYERID playerID = pRakServer->GetIndexFromPlayerID(sender);

				if (!pPlayerPool->IsPlayerConnected(playerID))
					return;

				unsigned char ReasonID;
				unsigned short KillerID;

				bsData.Read(ReasonID);
				bsData.Read(KillerID);

				if (KillerID != 0xFFFF)
				{
					if (KillerID < 0 || KillerID >= MAX_PLAYERS)
						return;

					if (!pPlayerPool->IsPlayerConnected(KillerID))
						return;

					if (ReasonID == 46 || ReasonID == 48 || ReasonID == 49)
						return;
				}

				RakNet::BitStream bsDeath;

				bsDeath.Write((unsigned short)playerID);
				pRakServer->RPC(&RPC_WorldPlayerDeath, &bsDeath, HIGH_PRIORITY, RELIABLE_ORDERED, 0, pRakServer->GetPlayerIDFromIndex(playerID), TRUE, FALSE, UNASSIGNED_NETWORK_ID, NULL);

				// OnPlayerDeath
			}

			void MapMarker(RPCParameters* rpcParams)
			{
				RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
				mimp::internal::player::PlayerPool* pPlayerPool = internal::server::GetServerInstance()->getPlayerPool();

				PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
				int iBitLength = rpcParams->numberOfBitsOfData;
				PlayerID sender = rpcParams->sender;

				RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);
				PLAYERID playerID = pRakServer->GetIndexFromPlayerID(sender);

				if (!pPlayerPool->IsPlayerConnected(playerID))
					return;

				float vecPos[3];
				bsData.Read(vecPos[0]);
				bsData.Read(vecPos[1]);
				bsData.Read(vecPos[2]);

				// OnPlayerClickMap
				
			}

			void DialogResponse(RPCParameters* rpcParams)
			{
				RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
				mimp::internal::player::PlayerPool* pPlayerPool = internal::server::GetServerInstance()->getPlayerPool();

				PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
				int iBitLength = rpcParams->numberOfBitsOfData;
				PlayerID sender = rpcParams->sender;

				RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);
				PLAYERID playerID = pRakServer->GetIndexFromPlayerID(sender);

				if (!pPlayerPool->IsPlayerConnected(playerID))
					return;

				WORD wDialogID;
				BYTE bButtonID;
				WORD wListBoxItem;
				char szInputResp[128 + 1];
				unsigned char iInputRespLen;

				bsData.Read(wDialogID);
				bsData.Read(bButtonID);
				bsData.Read(wListBoxItem);
				bsData.Read(iInputRespLen);
				bsData.Read(szInputResp, iInputRespLen);
				szInputResp[iInputRespLen] = 0;

				// OnDialogResponse
				
			}

			void SetInteriorId(RPCParameters* rpcParams)
			{
				RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
				mimp::internal::player::PlayerPool* pPlayerPool = internal::server::GetServerInstance()->getPlayerPool();

				PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
				int iBitLength = rpcParams->numberOfBitsOfData;
				PlayerID sender = rpcParams->sender;

				RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);
				PLAYERID playerID = pRakServer->GetIndexFromPlayerID(sender);

				if (!pPlayerPool->IsPlayerConnected(playerID))
					return;

				BYTE byteInteriorId;
				bsData.Read(byteInteriorId);

				mimp::Player* pPlayer = pPlayerPool->Get(playerID);

				pPlayer->setInteriorId(byteInteriorId);

				// OnPlayerInteriorChange
				
			}

			void ScmEvent(RPCParameters* rpcParams)
			{
				RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
				mimp::internal::player::PlayerPool* pPlayerPool = internal::server::GetServerInstance()->getPlayerPool();

				PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
				int iBitLength = rpcParams->numberOfBitsOfData;
				PlayerID sender = rpcParams->sender;

				RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);
				PLAYERID playerID = pRakServer->GetIndexFromPlayerID(sender);

				if (!pPlayerPool->IsPlayerConnected(playerID))
					return;

				int iEvent;

				DWORD dwParams1;
				DWORD dwParams2;
				DWORD dwParams3;

				bsData.Read(iEvent);

				bsData.Read(dwParams1);
				bsData.Read(dwParams2);
				bsData.Read(dwParams3);

				// OnSCM
				
			}

			void RegisterServerRPCs(RakServerInterface* pRakServer)
			{
				// Core RPCs
				pRakServer->RegisterAsRemoteProcedureCall(&RPC_ClientJoin, ClientJoin);
				pRakServer->RegisterAsRemoteProcedureCall(&RPC_RequestClass, RequestClass);
				pRakServer->RegisterAsRemoteProcedureCall(&RPC_RequestSpawn, RequestSpawn);
				pRakServer->RegisterAsRemoteProcedureCall(&RPC_Spawn, Spawn);
				pRakServer->RegisterAsRemoteProcedureCall(&RPC_Chat, Chat);
				pRakServer->RegisterAsRemoteProcedureCall(&RPC_UpdateScoresPingsIPs, UpdateScoresPingsIPs);
				pRakServer->RegisterAsRemoteProcedureCall(&RPC_DamageVehicle, DamageVehicle);
				pRakServer->RegisterAsRemoteProcedureCall(&RPC_EnterVehicle, EnterVehicle);
				pRakServer->RegisterAsRemoteProcedureCall(&RPC_ExitVehicle, ExitVehicle);
				pRakServer->RegisterAsRemoteProcedureCall(&RPC_ServerCommand, ServerCommand);
				pRakServer->RegisterAsRemoteProcedureCall(&RPC_Death, Death);
				pRakServer->RegisterAsRemoteProcedureCall(&RPC_MapMarker, MapMarker);
				pRakServer->RegisterAsRemoteProcedureCall(&RPC_DialogResponse, DialogResponse);
				pRakServer->RegisterAsRemoteProcedureCall(&RPC_SetInteriorId, SetInteriorId);
				pRakServer->RegisterAsRemoteProcedureCall(&RPC_ScmEvent, ScmEvent);
			}

			void UnRegisterServerRPCs(RakServerInterface* pRakServer)
			{
				// Core RPCs
				pRakServer->UnregisterAsRemoteProcedureCall(&RPC_ClientJoin);
				pRakServer->UnregisterAsRemoteProcedureCall(&RPC_RequestClass);
				pRakServer->UnregisterAsRemoteProcedureCall(&RPC_RequestSpawn);
				pRakServer->UnregisterAsRemoteProcedureCall(&RPC_Spawn);
				pRakServer->UnregisterAsRemoteProcedureCall(&RPC_Chat);
				pRakServer->UnregisterAsRemoteProcedureCall(&RPC_UpdateScoresPingsIPs);
				pRakServer->UnregisterAsRemoteProcedureCall(&RPC_DamageVehicle);
				pRakServer->UnregisterAsRemoteProcedureCall(&RPC_EnterVehicle);
				pRakServer->UnregisterAsRemoteProcedureCall(&RPC_ExitVehicle);
				pRakServer->UnregisterAsRemoteProcedureCall(&RPC_ServerCommand);
				pRakServer->UnregisterAsRemoteProcedureCall(&RPC_MapMarker);
				pRakServer->UnregisterAsRemoteProcedureCall(&RPC_DialogResponse);
				pRakServer->UnregisterAsRemoteProcedureCall(&RPC_SetInteriorId);
				pRakServer->UnregisterAsRemoteProcedureCall(&RPC_ScmEvent);
			}
		}
	}
}
