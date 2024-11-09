#include <MiServerxx/RPC/RPC.hpp>
#include <MiServerxx/RPC/RPCList.hpp>
#include <MiRak/RakServer.h>
#include <MiRak/BitStream.h>
#include <MiServerxx/core/Core.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/MiServerxx.hpp>
#include <MiServerxx/netgame/NetGame.hpp>

namespace mimp
{
	namespace internal
	{
		namespace RPC
		{
			namespace incoming
			{
				void Handler::ClientJoin(RPCParameters *rpcParams)
				{
					mimp::ServerConfig cfg = internal::server::GetCoreInstance()->getConfig();
					RakServerInterface *pRakServer = internal::server::GetCoreInstance()->getRakServer();
					CPool<CPlayer> *pPlayerPool = internal::server::GetCoreInstance()->GetNetGame()->GetPlayerPool();

					char *Data = reinterpret_cast<char *>(rpcParams->input);
					int iBitLength = rpcParams->numberOfBitsOfData;
					PlayerID sender = rpcParams->sender;

					RakNet::BitStream bsData((unsigned char *)Data, (iBitLength / 8) + 1, false);
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
						byteRejectReason = REJECT_REASON_BAD_PLAYERID;
						bsReject.Write(byteRejectReason);
						pRakServer->RPC(&outgoing::RPC_ConnectionRejected, &bsReject, HIGH_PRIORITY, RELIABLE,
										0, sender, FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
						pRakServer->Kick(sender);
						return;
					}

					if (iVersion != NETGAME_VERSION || RakNet::RakEncr::m_srvChallenge != (uiChallengeResponse ^ NETGAME_VERSION))
					{
						byteRejectReason = REJECT_REASON_BAD_VERSION;
						bsReject.Write(byteRejectReason);
						pRakServer->RPC(&outgoing::RPC_ConnectionRejected, &bsReject, HIGH_PRIORITY, RELIABLE,
										0, sender, FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
						pRakServer->Kick(sender);
						return;
					}

					pPlayerPool->InsertAt(playerID, new mimp::CPlayer(rpcParams->sender, playerID, szNickName));

					outgoing::Handler::InitGame(playerID,
												cfg.zoneNames,
												cfg.useCJWalk,
												cfg.allowedWeapons,
												cfg.limitGlobalChatRadius,
												cfg.globalChatRadius,
												cfg.stuntBonus,
												cfg.nameTagDrawDistance,
												cfg.disableEnterExits,
												cfg.nameTagLOS,
												cfg.manualVehicleEngineAndLight,
												cfg.spawnsAvailable,
												cfg.showPlayerTags,
												cfg.showPlayerMarkers,
												cfg.worldTime,
												cfg.weather,
												cfg.gravity,
												cfg.lanMode,
												cfg.deathDropMoney,
												cfg.instagib,
												cfg.netModeNormalOnfootSendRate,
												cfg.netModeNormalIncarSendRate,
												cfg.netModeFiringSendRate,
												cfg.netModeSendMultiplier,
												cfg.lagCompensation);

					// InitGameForPlayer(playerID);
					SendPlayerPoolToPlayer(playerID);
					SpawnAllVehiclesForPlayer(playerID);
					
					MIMP_GET_EVENT(PLAYERCONNECT, internal::server::GetCoreInstance()
						->getEventPool())
						PLAYERCONNECT->Emit(pPlayerPool->GetAt(playerID));
					
				}
			}
		}
	}
}
