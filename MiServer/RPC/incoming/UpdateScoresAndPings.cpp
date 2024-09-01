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
				void Handler::UpdateScoresAndPings(RPCParameters *rpcParams)
				{
					RakNet::BitStream bsUpdate;
					RakServerInterface *pRakServer = internal::server::GetServerInstance()->getRakServer();
					CPool<Player> *pPlayerPool = internal::server::GetServerInstance()->GetNetGame()->GetPlayerPool();
					for (Player *i : *pPlayerPool)
					{
						if (i != nullptr)
						{
							i->_setPing(pRakServer->GetLastPing(i->getRakPlayerId()));

							bsUpdate.Write(i);
							bsUpdate.Write(i->getScore());
							bsUpdate.Write(i->getPing());
						}
					}

					pRakServer->RPC(&incoming::RPC_UpdateScoresAndPings, &bsUpdate, HIGH_PRIORITY, RELIABLE, 0,
									rpcParams->sender, FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
				}
			}
		}
	}
}
