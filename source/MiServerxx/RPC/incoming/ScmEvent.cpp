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
void IRPCFunc_ScmEvent(RPCParameters* rpcParams)
{
	RakServerInterface* pRakServer = internal::server::GetCoreInstance()->getRakServer();
	CPool<CPlayer>* pPlayerPool = internal::server::GetCoreInstance()->GetNetGame()->GetPlayerPool();

	char* Data = reinterpret_cast<char*>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;
	PlayerID sender = rpcParams->sender;

	RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);
	WORD playerID = pRakServer->GetIndexFromPlayerID(sender);

	if (pPlayerPool->GetAt(playerID) == nullptr)
	{
		return;
	}

	int iEvent;

	DWORD dwParams1;
	DWORD dwParams2;
	DWORD dwParams3;

	bsData.Read(iEvent);

	bsData.Read(dwParams1);
	bsData.Read(dwParams2);
	bsData.Read(dwParams3);

	// OnSCM
}
