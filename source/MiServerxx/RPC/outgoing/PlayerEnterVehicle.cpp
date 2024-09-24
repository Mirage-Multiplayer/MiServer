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
                void Handler::PlayerEnterVehicle(const WORD playerid, const WORD vehicleid, const BYTE passenger)
                {
                    RakServerInterface *pRakServer = server::GetCoreInstance()->getRakServer();
                    RakNet::BitStream bs;
                    bs.Write(playerid);
                    bs.Write(vehicleid);
                    bs.Write(passenger);

                    pRakServer->RPC(&RPC_PlayerEnterVehicle, &bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
                                    pRakServer->GetPlayerIDFromIndex(playerid), true, false, UNASSIGNED_NETWORK_ID, nullptr);
                }
            }
        }
    }
}
