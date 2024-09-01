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
