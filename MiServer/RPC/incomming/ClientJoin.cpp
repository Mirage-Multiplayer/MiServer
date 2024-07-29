#include "RPC/RPC.hpp"
#include <MiRak/RakServer.h>
#include <MiRak/BitStream.h>

namespace mimp {
    namespace internal {
        namespace RPC {
            namespace incomming {
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

					pPlayerPool->Add(new mimp::Player(rpcParams->sender, playerID, szNickName));


					InitGameForPlayer(playerID);
					SendPlayerPoolToPlayer(playerID);
					SpawnAllVehiclesForPlayer(playerID);

					// OnPlayerConnect
				}
            }
        }
    }
}
