#include <MiServerxx/RPC/RPC.hpp>
#include <MiServerxx/RPC/RPCList.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiRak/BitStream.h>

namespace mimp
{
    namespace internal
    {
        namespace RPC
        {
            namespace outgoing
            {
                void Handler::SetPlayerArmour(const int playerid, const float value)
                {
                    RakServerInterface *pRakServer = server::GetCoreInstance()->getRakServer();
                    RakNet::BitStream bs;
                    bs.Write(value);

                    pRakServer->RPC(&RPC_SetPlayerArmour, &bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
                                    pRakServer->GetPlayerIDFromIndex(playerid), false, false, UNASSIGNED_NETWORK_ID, nullptr);
                }
            }
        }
    }
}
