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
                void Handler::PlayerExitVehicle(const WORD playerid, const WORD vehicleid)
                {
                    RakServerInterface *pRakServer = server::GetServerInstance()->getRakServer();
                    RakNet::BitStream bs;
                    bs.Write(playerid);
                    bs.Write(vehicleid);

                    pRakServer->RPC(&RPC_PlayerExitVehicle, &bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
                                    pRakServer->GetPlayerIDFromIndex(playerid), true, false, UNASSIGNED_NETWORK_ID, NULL);
                }
            }
        }
    }
}
