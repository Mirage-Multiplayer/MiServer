#include <MiServer/RPC/RPC.hpp>
#include <MiServer/RPC/RPCList.hpp>
#include <MiRak/RakServer.h>
#include <MiRak/BitStream.h>
#include <MiServer/server/Server.hpp>
#include <MiServer/server/ServerInstance.hpp>
#include <MiServer/MiServer.hpp>
#include <MiServer/netgame/NetGame.hpp>

namespace mimp
{
	namespace internal
	{
		namespace RPC
		{
			namespace incoming
			{
				void Handler::SendSpawn(RPCParameters *rpcParams)
				{
					RakServerInterface *pRakServer = internal::server::GetServerInstance()->getRakServer();
					CPool<Player> *pPlayerPool = internal::server::GetServerInstance()->GetNetGame()->GetPlayerPool();
					WORD playerId = (WORD)pRakServer->GetIndexFromPlayerID(rpcParams->sender);
					BYTE byteFightingStyle = 4;
					BYTE byteTeam = -1;
					int iSkin = 0;
					float vecPos[3] = {389.8672f, 2543.0046f, 16.5391f};
					float fRotation = 90.0f;
					DWORD dwColor = -1;

					if (pPlayerPool->GetAt(playerId) == nullptr)
					{
						return;
					}

					mimp::Player *pPlayer = pPlayerPool->GetAt(playerId);
					if (pPlayer == nullptr)
					{
						// Invalid player, usually not connected.
						return;
					}

					event::OnPlayerSpawn_params params;
					params.player = pPlayer;
					internal::server::GetServerInstance()->getEventPool()->Emit(event::SERVER_EVENT_PLAYERSPAWN, static_cast<void *>(&params));

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
