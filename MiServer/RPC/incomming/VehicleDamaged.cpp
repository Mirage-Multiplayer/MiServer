#include "RPC/RPC.hpp"

namespace mimp {
    namespace internal {
        namespace RPC {
            namespace incomming {
				void VehicleDamaged(RPCParameters* rpcParams)
				{
					RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
					internal::player::PlayerPool* pPlayerPool = internal::server::GetServerInstance()->getPlayerPool();

					PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
					int iBitLength = rpcParams->numberOfBitsOfData;
					PlayerID sender = rpcParams->sender;

					RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);
					PLAYERID playerID = pRakServer->GetIndexFromPlayerID(sender);

					if (!pPlayerPool->IsPlayerConnected(playerID))
						return;

					VEHICLEID vehID;
					uint32_t vehPanels;
					uint32_t vehDoors;
					uint8_t vehLights;
					uint8_t vehTires;

					bsData.Read(vehID);
					bsData.Read(vehPanels);
					bsData.Read(vehDoors);
					bsData.Read(vehLights);
					bsData.Read(vehTires);

					if (vehID == (VEHICLEID)-1)
					{
						//SendClientMessage(playerID, -1, "You are sending an invalid vehicle ID. Unlike kye, we wont kick you :)");
						return;
					}

					// OnPlayerDamageVehicle

					RakNet::BitStream bsDamage;

					bsDamage.Write(vehID);
					bsDamage.Write(vehPanels);
					bsDamage.Write(vehDoors);
					bsDamage.Write(vehLights);
					bsDamage.Write(vehTires);

					pRakServer->RPC(&RPC_VehicleDamaged, &bsDamage, HIGH_PRIORITY, RELIABLE_ORDERED, 0, sender, TRUE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
				}
            }
        }
    }
}
