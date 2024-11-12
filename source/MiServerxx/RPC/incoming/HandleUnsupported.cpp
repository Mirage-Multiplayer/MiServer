#include <MiServerxx/RPC/RPC.hpp>
#include <MiServerxx/RPC/RPCList.hpp>
#include <MiRak/RakServer.h>
#include <MiRak/BitStream.h>
#include <MiServerxx/core/Core.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/MiServerxx.hpp>

using namespace mimp;
using namespace mimp::internal;
using namespace mimp::internal::RPC;

void IRPCFunc_Unsupported(RPCParameters* rpcParams)
{
	return;
}