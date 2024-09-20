#include <MiServerxx/RPC/RPC.hpp>
#include <MiServerxx/RPC/RPCList.hpp>
#include <MiRak/RakServer.h>
#include <MiRak/BitStream.h>
#include <MiServerxx/server/Server.hpp>
#include <MiServerxx/server/ServerInstance.hpp>
#include <MiServerxx/MiServerxx.hpp>

namespace mimp
{
    namespace internal
    {
        namespace RPC
        {
            namespace incoming
            {
                void Handler::HandleUnsupported(RPCParameters *rpcParams)
                {
                    return;
                }
            }
        }
    }
}