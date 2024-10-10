#include <MiServerxx/RPC/RPC.hpp>
#include <MiServerxx/core/CoreInstance.hpp>

namespace mimp
{
    namespace internal
    {
        namespace RPC
        {
            namespace outgoing
            {
                void Handler::SetCheckpoint(const int playerid, const float x, const float y, const float z, const float sz)
                {
                    RakServerInterface *pRakServer = server::GetCoreInstance()->getRakServer();
                    RakNet::BitStream bs;
                    bs.Write(x);
                    bs.Write(y);
                    bs.Write(z);
                    bs.Write(sz);

                    pRakServer->RPC(&RPC_SetCheckpoint, &bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
                                    pRakServer->GetPlayerIDFromIndex(playerid), false, false, UNASSIGNED_NETWORK_ID, nullptr);
                }
            }
        }
    }
}
