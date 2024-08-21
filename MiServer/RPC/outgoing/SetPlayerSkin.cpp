#include <MiServer/RPC/RPCList.hpp>
#include <MiServer/server/Server.hpp>
#include <MiServer/server/ServerInstance.hpp>
#include <MiServer/MiServer.hpp>

namespace mimp
{
    namespace internal
    {
        namespace RPC
        {
            namespace outgoing
            {
                void Handler::SetPlayerSkin(const int playerid, const int skinid)
                {
                    RakServerInterface *pRakServer = server::GetServerInstance()->getRakServer();
                    RakNet::BitStream bs;
                    bs.Write(skinid);

                    pRakServer->RPC(&RPC_SetPlayerFacingAngle, &bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
                                    pRakServer->GetPlayerIDFromIndex(playerid), false, false, UNASSIGNED_NETWORK_ID, nullptr);
                }
            }
        }
    }
}
