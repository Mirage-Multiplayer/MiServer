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

void IRPCFunc_InteriorChangeNotification(RPCParameters* rpcParams) {
	RakServerInterface* pRakServer = internal::server::GetCoreInstance()->getRakServer();
	CPool<CPlayer>* pPlayerPool = internal::server::GetCoreInstance()->GetNetGame()->GetPlayerPool();

	char* Data = reinterpret_cast<char*>(rpcParams->input);
	int iBitLength = rpcParams->numberOfBitsOfData;
	PlayerID sender = rpcParams->sender;

	RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);
	WORD playerID = pRakServer->GetIndexFromPlayerID(sender);

	if (pPlayerPool->GetAt(playerID) == nullptr) {
		return;
	}

	BYTE byteInteriorId;
	bsData.Read(byteInteriorId);

	mimp::CPlayer* pPlayer = pPlayerPool->GetAt(playerID);

	pPlayer->_setInteriorId(byteInteriorId);

	// OnPlayerInteriorChange

}
