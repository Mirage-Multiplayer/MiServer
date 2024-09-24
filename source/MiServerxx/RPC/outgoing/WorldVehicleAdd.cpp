#include <MiServerxx/RPC/RPC.hpp>
#include <MiServerxx/RPC/RPCList.hpp>
#include <MiRak/RakServer.h>
#include <MiRak/BitStream.h>
#include <MiServerxx/core/Core.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/MiServerxx.hpp>

namespace mimp
{
    namespace internal
    {
        namespace RPC
        {
            namespace outgoing
            {
                void Handler::WorldVehicleAdd(CVehicle *veh, const int playerid)
                {
                    RakServerInterface *pRakServer = internal::server::GetCoreInstance()->getRakServer();

                    internal::packet::NEW_VEHICLE newVeh;
                    memset(&newVeh, 0, sizeof(internal::packet::NEW_VEHICLE));
                    newVeh.VehicleId = static_cast<WORD>(veh->getId());
                    newVeh.iVehicleType = veh->getModelId();
                    float x, y, z;
                    veh->getPosition(x, y, z);
                    newVeh.vecPos[0] = x;
                    newVeh.vecPos[1] = y;
                    newVeh.vecPos[2] = z;
                    newVeh.fRotation = veh->getRotation();
                    newVeh.fHealth = veh->getHealth();
                    newVeh.byteInterior = 0;
                    newVeh.dwDoorDamageStatus = 0;
                    newVeh.dwPanelDamageStatus = 0;
                    newVeh.byteLightDamageStatus = 0;

                    RakNet::BitStream bs;
                    bs.Write((const char *)&newVeh, sizeof(internal::packet::NEW_VEHICLE));
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
