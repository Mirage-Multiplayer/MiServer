#include <MiServerxx/RPC/RPC.hpp>
// #include <MiServerxx/RPC/RPCList.hpp>
#include <MiServerxx/core/CoreInstance.hpp>

namespace mimp
{
    namespace internal
    {
        namespace RPC
        {
            namespace outgoing
            {
                void Handler::DisableCheckpoint(const int playerid)
                {
                    RakServerInterface *pRakServer = server::GetCoreInstance()->getRakServer();
                    RakNet::BitStream bs;

                    pRakServer->RPC(&RPC_DisableCheckpoint, nullptr, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
                                    pRakServer->GetPlayerIDFromIndex(playerid), false, false, UNASSIGNED_NETWORK_ID, nullptr);
                }
            }
        }
    }
}
