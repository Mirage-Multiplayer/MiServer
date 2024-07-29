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

				svr->getRakServer()->RPC(&outgoing::RPC_InitGame, &bsInitGame, HIGH_PRIORITY, RELIABLE,
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
					pRakServer->RPC(&outgoing::RPC_ServerJoin, &bs, HIGH_PRIORITY, RELIABLE,
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
					pRakServer->RPC(&outgoing::RPC_WorldVehicleAdd, &bs, HIGH_PRIORITY, RELIABLE,
						0, pRakServer->GetPlayerIDFromIndex(playerID), FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);

					Sleep(5); // well, shit.
				}
			}

			void RegisterServerRPCs(RakServerInterface* pRakServer)
			{
				// Core RPCs
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_ClientJoin, incomming::ClientJoin);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_RequestClass, incomming::RequestClass);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_RequestSpawn, incomming::RequestSpawn);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_SendSpawn, incomming::SendSpawn);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_ChatMessage, incomming::ChatMessage);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_UpdateScoresAndPings, incomming::UpdateScoresAndPings);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_VehicleDamaged, incomming::VehicleDamaged);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_EnterVehicle, incomming::EnterVehicle);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_ExitVehicle, incomming::ExitVehicle);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_SendCommand, incomming::SendCommand);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_DeathNotification, incomming::DeathNotification);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_MapMarker, incomming::MapMarker);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_DialogResponse, incomming::DialogResponse);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_InteriorChangeNotification, incomming::InteriorChangeNotification);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_ScmEvent, incomming::ScmEvent);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_CameraTarget, incomming::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_ClickPlayer, incomming::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_ClientCheckResponse, incomming::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_VehicleDestroyed, incomming::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_EditAttachedObject, incomming::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_EditObject, incomming::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_GiveActorDamage, incomming::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_GiveTakeDamage, incomming::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_MapMarker, incomming::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_MenuQuit, incomming::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_NPCJoin, incomming::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_PickedUpPickup, incomming::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_SelectObject, incomming::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incomming::RPC_SelectTextDraw, incomming::HandleUnsupported);
			}
			void UnRegisterServerRPCs(RakServerInterface* pRakServer)
			{

				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_ClientJoin);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_RequestClass);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_RequestSpawn);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_SendSpawn);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_ChatMessage);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_UpdateScoresAndPings);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_VehicleDamaged);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_EnterVehicle);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_ExitVehicle);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_SendCommand);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_DeathNotification);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_MapMarker);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_DialogResponse);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_InteriorChangeNotification);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_ScmEvent);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_CameraTarget);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_ClickPlayer);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_ClientCheckResponse);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_VehicleDestroyed);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_EditAttachedObject);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_EditObject);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_GiveActorDamage);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_GiveTakeDamage);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_MapMarker);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_MenuQuit);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_NPCJoin);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_PickedUpPickup);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_SelectObject);
				pRakServer->UnregisterAsRemoteProcedureCall(&incomming::RPC_SelectTextDraw);
			}
		}
	}
}
