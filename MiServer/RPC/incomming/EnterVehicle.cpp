#include "RPC/RPC.hpp"
#include "server/ServerInstance.hpp"
namespace mimp {
    namespace internal {
        namespace RPC {
            namespace incomming {
				void Handler::EnterVehicle(RPCParameters* rpcParams)
				{
					RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
					mimp::internal::player::PlayerPool* pPlayerPool = internal::server::GetServerInstance()->getPlayerPool();

					PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
					int iBitLength = rpcParams->numberOfBitsOfData;
					PlayerID sender = rpcParams->sender;

					RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);
					PLAYERID playerID = pRakServer->GetIndexFromPlayerID(sender);

					if (!pPlayerPool->IsPlayerConnected(playerID))
						return;

					VEHICLEID VehicleID = 0;
					BYTE bytePassenger = 0;

					bsData.Read(VehicleID);
					bsData.Read(bytePassenger);

					if (VehicleID == (VEHICLEID)-1)
					{
						//SendClientMessage(playerID, -1, "You are sending an invalid vehicle ID. Unlike kye, we wont kick you :)");
						return;
					}

					// OnPlayerEnterVehicle

					mimp::Player* pPlayer = pPlayerPool->Get(playerID);
					pPlayer->getInCarSyncData()->VehicleID = VehicleID;

					RakNet::BitStream bsVehicle;
					bsVehicle.Write(playerID);
					bsVehicle.Write(VehicleID);
					bsVehicle.Write(bytePassenger);
					pRakServer->RPC(&RPC_EnterVehicle, &bsVehicle, HIGH_PRIORITY, RELIABLE_ORDERED,
						0, sender, TRUE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
				}
            }
        }
    }
}
