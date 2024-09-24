#include <MiServerxx/RPC/RPC.hpp>
#include <MiServerxx/RPC/RPCList.hpp>
#include <MiRak/RakServer.h>
#include <MiRak/BitStream.h>
#include <MiServerxx/core/Core.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/MiServerxx.hpp>
#include <MiServerxx/netgame/NetGame.hpp>

namespace mimp
{
	namespace internal
	{
		namespace RPC
		{
			namespace incoming
			{
				void Handler::VehicleDamaged(RPCParameters *rpcParams)
				{
					RakServerInterface *pRakServer = internal::server::GetCoreInstance()->getRakServer();
					CPool<CPlayer> *pPlayerPool = internal::server::GetCoreInstance()->GetNetGame()->GetPlayerPool();

					char *Data = reinterpret_cast<char *>(rpcParams->input);
					int iBitLength = rpcParams->numberOfBitsOfData;
					PlayerID sender = rpcParams->sender;

					RakNet::BitStream bsData((unsigned char *)Data, (iBitLength / 8) + 1, false);
					WORD playerID = pRakServer->GetIndexFromPlayerID(sender);

					if (pPlayerPool->GetAt(playerID) == nullptr)
					{
						return;
					}

					WORD vehID;
					uint32_t vehPanels;
					uint32_t vehDoors;
					uint8_t vehLights;
					uint8_t vehTires;

					bsData.Read(vehID);
					bsData.Read(vehPanels);
					bsData.Read(vehDoors);
					bsData.Read(vehLights);
					bsData.Read(vehTires);

					if (vehID == (WORD)-1)
					{
						// SendClientMessage(playerID, -1, "You are sending an invalid vehicle ID. Unlike kye, we wont kick you :)");
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
