#include <MiServer/RPC/RPC.hpp>
#include <MiServer/RPC/RPCList.hpp>
#include <MiRak/RakServer.h>
#include <MiRak/BitStream.h>
#include <MiServer/server/Server.hpp>
#include <MiServer/server/ServerInstance.hpp>
#include <MiServer/MiServer.hpp>
#include <MiServer/player/defines.hpp>
#include <MiServer/vehicle/VehiclePool.hpp>
#include <MiServer/vehicle/Vehicle.hpp>

namespace mimp
{
	namespace internal
	{
		namespace RPC
		{
			namespace incoming
			{
				void Handler::UpdateScoresAndPings(RPCParameters *rpcParams)
				{
					RakNet::BitStream bsUpdate;
					RakServerInterface *pRakServer = internal::server::GetServerInstance()->getRakServer();
					internal::player::PlayerPool *pPlayerPool = internal::server::GetServerInstance()->getPlayerPool();
					for (PLAYERID i = 0; i < MAX_PLAYERS; i++)
					{
						if (pPlayerPool->IsPlayerConnected(i))
						{
							pPlayerPool->Get(i)->_setPing(pRakServer->GetLastPing(pPlayerPool->Get(i)->getRakPlayerId()));

							bsUpdate.Write(i);
							bsUpdate.Write(pPlayerPool->Get(i)->getScore());
							bsUpdate.Write(pPlayerPool->Get(i)->getPing());
						}
					}

					pRakServer->RPC(&incoming::RPC_UpdateScoresAndPings, &bsUpdate, HIGH_PRIORITY, RELIABLE, 0,
									rpcParams->sender, FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
				}
			}
		}
	}
}
