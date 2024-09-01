#include <MiServer/RPC/RPC.hpp>
#include <MiServer/RPC/RPCList.hpp>
#include <MiRak/RakServer.h>
#include <MiRak/BitStream.h>
#include <MiServer/server/Server.hpp>
#include <MiServer/server/ServerInstance.hpp>
#include <MiServer/MiServer.hpp>
#include <MiServer/netgame/NetGame.hpp>

namespace mimp
{
	namespace internal
	{
		namespace RPC
		{
			namespace incoming
			{
				void Handler::ExitVehicle(RPCParameters *rpcParams)
				{
					RakServerInterface *pRakServer = internal::server::GetServerInstance()->getRakServer();
					CPool<Player> *pPlayerPool = internal::server::GetServerInstance()->GetNetGame()->GetPlayerPool();

					char *Data = reinterpret_cast<char *>(rpcParams->input);
					int iBitLength = rpcParams->numberOfBitsOfData;
					PlayerID sender = rpcParams->sender;

					RakNet::BitStream bsData((unsigned char *)Data, (iBitLength / 8) + 1, false);
					WORD playerID = pRakServer->GetIndexFromPlayerID(sender);

					if (pPlayerPool->GetAt(playerID) == nullptr)
					{
						return;
					}

					WORD VehicleID;
					bsData.Read(VehicleID);

					if (VehicleID == (WORD)-1)
					{
						// SendClientMessage(playerID, -1, "You are sending an invalid vehicle ID. Unlike kye, we wont kick you :)");
						return;
					}

					// OnPlayerExitVehicle

					mimp::Player *pPlayer = pPlayerPool->GetAt(playerID);
					pPlayer->getInCarSyncData()->VehicleID = -1;

					outgoing::Handler::PlayerExitVehicle(playerID, VehicleID);
				}
			}
		}
	}
}
