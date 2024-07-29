#include "RPC/RPC.hpp"

namespace mimp {
    namespace internal {
        namespace RPC {
            namespace incomming {
				void ExitVehicle(RPCParameters* rpcParams)
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

					VEHICLEID VehicleID;
					bsData.Read(VehicleID);

					if (VehicleID == (VEHICLEID)-1)
					{
						//SendClientMessage(playerID, -1, "You are sending an invalid vehicle ID. Unlike kye, we wont kick you :)");
						return;
					}

					// OnPlayerExitVehicle

					mimp::Player* pPlayer = pPlayerPool->Get(playerID);
					pPlayer->getInCarSyncData()->VehicleID = -1;

					RakNet::BitStream bsVehicle;
					bsVehicle.Write(playerID);
					bsVehicle.Write(VehicleID);
					pRakServer->RPC(&RPC_ExitVehicle, &bsVehicle, HIGH_PRIORITY, RELIABLE_ORDERED,
						0, sender, TRUE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
				}
            }
        }
    }
}
