#include "RPC/RPC.hpp"
#include "RPC/RPCList.hpp"

namespace mimp {
    namespace internal {
        namespace RPC {
            namespace incomming {
                void Handler::HandleUnsupported(RPCParameters* rpcParams) {
                    return;
                }
            }
        }
    }
}