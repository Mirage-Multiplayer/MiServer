#include <MiServer/RPC/RPC.hpp>
#include <MiServer/RPC/RPCList.hpp>
#include <MiRak/RakServer.h>
#include <MiRak/BitStream.h>
#include <MiServer/server/Server.hpp>
#include <MiServer/server/ServerInstance.hpp>
#include <MiServer/MiServer.hpp>

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
                    RakServerInterface *pRakServer = server::GetServerInstance()->getRakServer();
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
