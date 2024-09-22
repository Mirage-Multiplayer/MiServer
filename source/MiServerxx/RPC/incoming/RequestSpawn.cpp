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
				void Handler::RequestSpawn(RPCParameters *rpcParams)
				{
					RakNet::BitStream bsReply;

					bsReply.Write((BYTE)2);
					RakServerInterface *pRakServer = internal::server::GetServerInstance()->getRakServer();
					pRakServer->RPC(&RPC_RequestSpawn, &bsReply, HIGH_PRIORITY, RELIABLE,
									0, rpcParams->sender, FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
				}
			}
		}
	}
}
