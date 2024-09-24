#include <MiServerxx/RPC/RPC.hpp>
#include <MiServerxx/RPC/RPCList.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiRak/RakServer.h>
#include <MiRak/BitStream.h>

namespace mimp
{
    namespace internal
    {
        namespace RPC
        {
            namespace outgoing
            {
                void Handler::SetPlayerColor(const int playerid, const unsigned long color)
                {
                    RakServerInterface *pRakServer = server::GetCoreInstance()->getRakServer();
                    RakNet::BitStream bs;
                    bs.Write(color);

                    pRakServer->RPC(&RPC_SetPlayerColor, &bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
                                    pRakServer->GetPlayerIDFromIndex(playerid), false, false, UNASSIGNED_NETWORK_ID, nullptr);
                }
            }
        }
    }
}
