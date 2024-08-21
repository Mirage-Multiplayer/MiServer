#include <MiServer/RPC/RPC.hpp>
#include <MiServer/RPC/RPCList.hpp>
#include <MiRak/RakServer.h>
#include <MiRak/BitStream.h>
#include <MiServer/server/Server.hpp>
#include <MiServer/server/ServerInstance.hpp>
#include <MiServer/MiServer.hpp>
#include <MiServer/player/defines.hpp>
#include <MiServer/vehicle/VehiclePool.hpp>
#include <MiServer/vehicle/Vehicle.hpp>

namespace mimp
{
	namespace internal
	{
		namespace RPC
		{
			namespace incoming
			{
				void Handler::ScmEvent(RPCParameters *rpcParams)
				{
					RakServerInterface *pRakServer = internal::server::GetServerInstance()->getRakServer();
					mimp::internal::player::PlayerPool *pPlayerPool = internal::server::GetServerInstance()->getPlayerPool();

					char *Data = reinterpret_cast<char *>(rpcParams->input);
					int iBitLength = rpcParams->numberOfBitsOfData;
					PlayerID sender = rpcParams->sender;

					RakNet::BitStream bsData((unsigned char *)Data, (iBitLength / 8) + 1, false);
					PLAYERID playerID = pRakServer->GetIndexFromPlayerID(sender);

					if (!pPlayerPool->IsPlayerConnected(playerID))
						return;

					int iEvent;

					DWORD dwParams1;
					DWORD dwParams2;
					DWORD dwParams3;

					bsData.Read(iEvent);

					bsData.Read(dwParams1);
					bsData.Read(dwParams2);
					bsData.Read(dwParams3);

					// OnSCM
				}
			}
		}
	}
}
