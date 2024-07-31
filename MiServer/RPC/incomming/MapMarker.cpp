#include "RPC/RPC.hpp"
#include "server/ServerInstance.hpp"
namespace mimp {
    namespace internal {
        namespace RPC {
            namespace incomming {
				void Handler::MapMarker(RPCParameters* rpcParams)
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

					float vecPos[3];
					bsData.Read(vecPos[0]);
					bsData.Read(vecPos[1]);
					bsData.Read(vecPos[2]);

					// OnPlayerClickMap

				}
            }
        }
    }
}
