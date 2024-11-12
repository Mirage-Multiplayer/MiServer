#include <MiServerxx/RPC/RPC.hpp>
#include <MiServerxx/RPC/RPCList.hpp>
#include <MiRak/RakServer.h>
#include <MiRak/BitStream.h>
#include <MiServerxx/core/Core.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/MiServerxx.hpp>
#include <MiServerxx/netgame/NetGame.hpp>

using namespace mimp;
using namespace mimp::internal;
using namespace mimp::internal::RPC;
void IRPCFunc_UpdateScoresAndPings(RPCParameters* rpcParams)
{
	ORPCUpdateScoresAndPings rpc;
	RakNet::BitStream bsUpdate;
	RakServerInterface* pRakServer = internal::server::GetCoreInstance()->getRakServer();
	CPool<CPlayer>* pPlayerPool = internal::server::GetCoreInstance()->GetNetGame()->GetPlayerPool();
	for (CPlayer* i : *pPlayerPool)
	{
		if (i != nullptr)
		{
			i->_setPing(pRakServer->GetLastPing(i->getRakPlayerId()));

			bsUpdate.Write(i);
			bsUpdate.Write(i->getScore());
			bsUpdate.Write(i->getPing());
		}
	}

	int uid = rpc.GetUID();
	pRakServer->RPC(&uid, &bsUpdate, HIGH_PRIORITY, RELIABLE, 0,
		rpcParams->sender, FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
}
