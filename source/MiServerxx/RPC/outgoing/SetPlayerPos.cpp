#include <MiServerxx/RPC/RPC.hpp>
#include <MiServerxx/RPC/RPCList.hpp>
#include <MiServerxx/server/Server.hpp>
#include <MiServerxx/server/ServerInstance.hpp>
#include <MiServerxx/MiServerxx.hpp>
namespace mimp
{
    namespace internal
    {
        namespace RPC
        {
            namespace outgoing
            {
                void Handler::SetPlayerPos(const int playerid, const float x, const float y, const float z)
                {
                    RakServerInterface *pRakServer = server::GetServerInstance()->getRakServer();
                    RakNet::BitStream bs;
                    bs.Write(x);
                    bs.Write(y);
                    bs.Write(z);

                    pRakServer->RPC(&RPC_SetPlayerPos, &bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
                                    pRakServer->GetPlayerIDFromIndex(playerid), false, false, UNASSIGNED_NETWORK_ID, nullptr);
                }
            }
        }
    }
}
