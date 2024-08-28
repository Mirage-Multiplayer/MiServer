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
				void Handler::EnterVehicle(RPCParameters *rpcParams)
				{
					std::cout << "Enter vehicle\n";
					RakServerInterface *pRakServer = internal::server::GetServerInstance()->getRakServer();
					mimp::internal::player::PlayerPool *pPlayerPool = internal::server::GetServerInstance()->getPlayerPool();

					char *Data = reinterpret_cast<char *>(rpcParams->input);
					int iBitLength = rpcParams->numberOfBitsOfData;
					PlayerID sender = rpcParams->sender;

					RakNet::BitStream bsData((unsigned char *)Data, (iBitLength / 8) + 1, false);
					PLAYERID playerID = pRakServer->GetIndexFromPlayerID(sender);

					if (!pPlayerPool->IsPlayerConnected(playerID))
						return;

					VEHICLEID VehicleID = 0;
					bsData.Read(VehicleID);
					BYTE bytePassenger = 0;
					bsData.Read(bytePassenger);

					if (VehicleID == (VEHICLEID)-1)
					{
						std::cout << "Fodase debug monstro\n";
						return;
					}

					// OnPlayerEnterVehicle

					mimp::Player *pPlayer = pPlayerPool->Get(playerID);
					pPlayer->getInCarSyncData()->VehicleID = VehicleID;

					outgoing::Handler::PlayerEnterVehicle(playerID, VehicleID, bytePassenger);
				}
			}
		}
	}
}
