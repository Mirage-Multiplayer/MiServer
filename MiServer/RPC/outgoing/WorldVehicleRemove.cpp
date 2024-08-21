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
            namespace outgoing
            {
                void Handler::WorldVehicleRemove(const VEHICLEID idx, const int playerid)
                {
                    vehicle::VehiclePool *pVehiclePool = server::GetServerInstance()->getVehiclePool();

                    if (!pVehiclePool->IsValidVehicle(idx))
                    {
                        return;
                    }

                    RakServerInterface *pRakServer = server::GetServerInstance()->getRakServer();
                    RakNet::BitStream bs;
                    bs.Write((const char *)&idx, sizeof(VEHICLEID));
                    if (playerid == -1)
                    {
                        pRakServer->RPC(&RPC_WorldVehicleAdd, &bs, HIGH_PRIORITY, RELIABLE,
                                        0, UNASSIGNED_PLAYER_ID, TRUE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
                    }
                    else
                    {
                        pRakServer->RPC(&RPC_WorldVehicleAdd, &bs, HIGH_PRIORITY, RELIABLE,
                                        0, pRakServer->GetPlayerIDFromIndex(playerid), FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
                    }
                }
            }
        }
    }
}
