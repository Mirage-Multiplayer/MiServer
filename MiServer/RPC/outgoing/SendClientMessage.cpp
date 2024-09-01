#include <MiServer/MiServer.hpp>
#include <MiServer/RPC/RPC.hpp>
#include <MiServer/RPC/RPCList.hpp>
#include <MiServer/server/Server.hpp>
#include <MiServer/server/ServerInstance.hpp>
#include <MiServer/event/EventTypes.hpp>
#include <MiServer/event/EventPool.hpp>

#include <MiRak/BitStream.h>
#include <cstdint>

namespace mimp
{
    namespace internal
    {
        namespace RPC
        {
            namespace outgoing
            {
                void Handler::SendClientMessage(const int playerid, const int color, const int messageLength, const char *message)
                {
                    RakServerInterface *pRakServer = server::GetServerInstance()->getRakServer();
                    RakNet::BitStream bs;
                    bs.Write(static_cast<uint32_t>(color));
                    bs.Write(static_cast<uint32_t>(messageLength));
                    bs.Write(message, messageLength);

                    pRakServer->RPC(&RPC_SendClientMessage, &bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
                                    pRakServer->GetPlayerIDFromIndex(playerid), false, false, UNASSIGNED_NETWORK_ID, nullptr);
                }
            }
        }
    }
}
