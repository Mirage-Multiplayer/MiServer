#include <MiServer/RPC/RPC.hpp>
#include <MiServer/RPC/RPCList.hpp>
#include <MiRak/RakServer.h>
#include <MiRak/BitStream.h>
#include <MiServer/server/Server.hpp>
#include <MiServer/server/ServerInstance.hpp>
#include <MiServer/MiServer.hpp>

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