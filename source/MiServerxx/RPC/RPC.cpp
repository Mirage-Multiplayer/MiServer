#include <MiRak/BitStream.h>
#include <MiRak/RakEncr.h>
#include <string>
#include <thread>
#include <MiServerxx/core/Core.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/MiServerxx.hpp>
#include <MiServerxx/types.h>
#include <MiServerxx/RPC/RPCList.hpp>
#include <MiServerxx/RPC/RPC.hpp>

#include <MiServerxx/packet/SyncData.hpp>
#include <MiServerxx/packet/defines.hpp>
#include <MiServerxx/netgame/NetGame.hpp>

namespace mimp
{
	namespace internal
	{
		namespace RPC
		{
			float m_fGravity = 0.008f;

			int iLagCompensation = 1;

			void InitGameForPlayer(WORD playerID)
			{
				mimp::CCore *svr = mimp::internal::server::GetCoreInstance();

				// TODO: Modify server config
				RakNet::BitStream bsInitGame;
				bsInitGame.WriteCompressed((bool)1); // m_bZoneNames
				bsInitGame.WriteCompressed((bool)1); // m_bUseCJWalk
				bsInitGame.WriteCompressed((bool)1); // m_bAllowWeapons
				bsInitGame.WriteCompressed((bool)0); // m_bLimitGlobalChatRadius
				bsInitGame.Write((float)200.00f);	 // m_fGlobalChatRadius
				bsInitGame.WriteCompressed((bool)0); // bStuntBonus
				bsInitGame.Write((float)70.0f);		 // m_fNameTagDrawDistance
				bsInitGame.WriteCompressed((bool)0); // m_bDisableEnterExits
				bsInitGame.WriteCompressed((bool)1); // m_bNameTagLOS
				bsInitGame.WriteCompressed((bool)0); // m_bManualVehicleEngineAndLight
				bsInitGame.Write((int)1);			 // m_iSpawnsAvailable
				bsInitGame.Write(playerID);			 // MyPlayerID
				bsInitGame.WriteCompressed((bool)1); // m_bShowPlayerTags
				bsInitGame.Write((int)1);			 // m_iShowPlayerMarkers
				bsInitGame.Write((BYTE)12);			 // m_byteWorldTime
				bsInitGame.Write((BYTE)10);			 // m_byteWeather
				bsInitGame.Write((float)m_fGravity); // m_fGravity
				bsInitGame.WriteCompressed((bool)0); // bLanMode
				bsInitGame.Write((int)0);			 // m_iDeathDropMoney
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
				bsInitGame.Write((char *)&vehModels, 212);

				svr->getRakServer()->RPC(&outgoing::RPC_InitGame, &bsInitGame, HIGH_PRIORITY, RELIABLE,
										 0, svr->getRakServer()->GetPlayerIDFromIndex(playerID), FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
			}

			void SendPlayerPoolToPlayer(WORD playerID)
			{
				CPool<CPlayer> *pPlayerPool = server::GetCoreInstance()->GetNetGame()->GetPlayerPool();
				RakServerInterface *pRakServer = server::GetCoreInstance()->getRakServer();

				// let the player know about all the players in the server
				for (CPlayer *p : *pPlayerPool)
				{
					if (p == nullptr)
					{
						return;
					}

					if (p->getPlayerId() == playerID)
						continue;

					BYTE byteNameLen = (BYTE)strlen(p->getNickName().c_str());
					RakNet::BitStream bs;
					bs.Reset();
					bs.Write(p);
					bs.Write((int)1);
					bs.Write((BYTE)0);
					bs.Write(byteNameLen);
					bs.Write(p->getNickName().c_str(), byteNameLen);
					pRakServer->RPC(&outgoing::RPC_ServerJoin, &bs, HIGH_PRIORITY, RELIABLE,
									0, pRakServer->GetPlayerIDFromIndex(playerID), FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);

					std::this_thread::sleep_for(std::chrono::milliseconds(5));
				}
			}

			void SpawnAllVehiclesForPlayer(WORD playerID)
			{
				RakServerInterface *pRakServer = server::GetCoreInstance()->getRakServer();
				CPool<CVehicle> *pVehiclePool = server::GetCoreInstance()->GetNetGame()->GetVehiclePool();
				// spawn all vehicles for this player
				for (CVehicle *v : *pVehiclePool)
				{
					if (v == nullptr)
					{
						continue;
					}
					float x, y, z;
					v->getPosition(x, y, z);

					internal::RPC::outgoing::Handler::WorldVehicleAdd(v, playerID);

					std::this_thread::sleep_for(std::chrono::milliseconds(5));
				}
			}

			void RegisterServerRPCs(RakServerInterface *pRakServer)
			{
				// Core RPCs
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_ClientJoin, incoming::Handler::ClientJoin);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_RequestClass, incoming::Handler::RequestClass);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_RequestSpawn, incoming::Handler::RequestSpawn);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_SendSpawn, incoming::Handler::SendSpawn);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_ChatMessage, incoming::Handler::ChatMessage);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_UpdateScoresAndPings, incoming::Handler::UpdateScoresAndPings);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_VehicleDamaged, incoming::Handler::VehicleDamaged);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_EnterVehicle, incoming::Handler::EnterVehicle);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_ExitVehicle, incoming::Handler::ExitVehicle);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_DeathNotification, incoming::Handler::DeathNotification);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_DialogResponse, incoming::Handler::DialogResponse);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_InteriorChangeNotification, incoming::Handler::InteriorChangeNotification);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_ScmEvent, incoming::Handler::ScmEvent);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_SendCommand, incoming::Handler::SendCommand);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_CameraTarget, incoming::Handler::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_ClickPlayer, incoming::Handler::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_ClientCheckResponse, incoming::Handler::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_VehicleDestroyed, incoming::Handler::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_EditAttachedObject, incoming::Handler::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_EditObject, incoming::Handler::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_GiveActorDamage, incoming::Handler::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_GiveTakeDamage, incoming::Handler::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_MapMarker, incoming::Handler::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_MenuQuit, incoming::Handler::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_NPCJoin, incoming::Handler::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_PickedUpPickup, incoming::Handler::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_SelectObject, incoming::Handler::HandleUnsupported);
				pRakServer->RegisterAsRemoteProcedureCall(&incoming::RPC_SelectTextDraw, incoming::Handler::HandleUnsupported);
			}
			void UnRegisterServerRPCs(RakServerInterface *pRakServer)
			{

				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_ClientJoin);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_RequestClass);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_RequestSpawn);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_SendSpawn);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_ChatMessage);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_UpdateScoresAndPings);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_VehicleDamaged);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_EnterVehicle);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_ExitVehicle);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_SendCommand);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_DeathNotification);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_DialogResponse);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_InteriorChangeNotification);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_ScmEvent);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_CameraTarget);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_ClickPlayer);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_ClientCheckResponse);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_VehicleDestroyed);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_EditAttachedObject);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_EditObject);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_GiveActorDamage);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_GiveTakeDamage);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_MapMarker);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_MenuQuit);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_NPCJoin);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_PickedUpPickup);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_SelectObject);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_SelectTextDraw);
				pRakServer->UnregisterAsRemoteProcedureCall(&incoming::RPC_SendCommand);
			}
		}
	}
}
