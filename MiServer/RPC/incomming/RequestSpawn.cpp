#include "RPC/RPC.hpp"
#include "event/EventTypes.hpp"
#include "server/ServerInstance.hpp"

namespace mimp {
    namespace internal {
        namespace RPC {
            namespace incomming {
				void Handler::RequestSpawn(RPCParameters* rpcParams)
				{
					RakNet::BitStream bsReply;

					bsReply.Write((BYTE)2);
					RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
					pRakServer->RPC(&RPC_RequestSpawn, &bsReply, HIGH_PRIORITY, RELIABLE,
						0, rpcParams->sender, FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
				}
            }
        }
    }
}
