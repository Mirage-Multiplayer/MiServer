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
				void Handler::UpdateScoresAndPings(RPCParameters *rpcParams)
				{
					RakNet::BitStream bsUpdate;
					RakServerInterface *pRakServer = internal::server::GetCoreInstance()->getRakServer();
					CPool<CPlayer> *pPlayerPool = internal::server::GetCoreInstance()->GetNetGame()->GetPlayerPool();
					for (CPlayer *i : *pPlayerPool)
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
