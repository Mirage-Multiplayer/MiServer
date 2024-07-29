#include "RPC/RPC.hpp"

namespace mimp {
    namespace internal {
        namespace RPC {
            namespace incomming {
				void ScmEvent(RPCParameters* rpcParams)
				{
					RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
					mimp::internal::player::PlayerPool* pPlayerPool = internal::server::GetServerInstance()->getPlayerPool();

					PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
					int iBitLength = rpcParams->numberOfBitsOfData;
					PlayerID sender = rpcParams->sender;

					RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);
					PLAYERID playerID = pRakServer->GetIndexFromPlayerID(sender);

					if (!pPlayerPool->IsPlayerConnected(playerID))
						return;

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
            }
        }
    }
}
