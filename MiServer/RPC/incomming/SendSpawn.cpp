#include "RPC/RPC.hpp"
#include "event/EventTypes.hpp"
#include "server/ServerInstance.hpp"

namespace mimp {
    namespace internal {
        namespace RPC {
            namespace incomming {
				void Handler::SendSpawn(RPCParameters* rpcParams)
				{
					RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
					internal::player::PlayerPool* pPlayerPool = internal::server::GetServerInstance()->getPlayerPool();
					PLAYERID playerId = (PLAYERID)pRakServer->GetIndexFromPlayerID(rpcParams->sender);
					BYTE byteFightingStyle = 4;
					BYTE byteTeam = -1;
					int iSkin = 0;
					float vecPos[3] = { 389.8672f, 2543.0046f, 16.5391f };
					float fRotation = 90.0f;
					DWORD dwColor = -1;

					if (!pPlayerPool->IsPlayerConnected(playerId))
						return;

					mimp::Player* pPlayer = pPlayerPool->Get(playerId);
					if (pPlayer == nullptr) {
						// Invalid player, usually not connected.
						return;
					}

					event::OnPlayerSpawn_params params;
					params.player = pPlayer;
					internal::server::GetServerInstance()->getEventPool()->Emit(event::SERVER_EVENT_PLAYERSPAWN, (void*)&params);

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
					pRakServer->RPC(&outgoing::RPC_WorldPlayerAdd, &bsData, HIGH_PRIORITY, RELIABLE_ORDERED,
						0, pRakServer->GetPlayerIDFromIndex(playerId), TRUE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
				}
            }
        }
    }
}
