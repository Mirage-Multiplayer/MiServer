#include <MiServer/MiServer.hpp>
#include <MiServer/RPC/RPC.hpp>
#include <MiServer/RPC/RPCList.hpp>
#include <MiServer/server/Server.hpp>
#include <MiServer/server/ServerInstance.hpp>
#include <MiServer/event/EventTypes.hpp>
#include <MiServer/event/EventPool.hpp>
#include <MiServer/netgame/NetGame.hpp>

namespace mimp
{
    namespace internal
    {
        namespace RPC
        {
            namespace incoming
            {
                void Handler::SendCommand(RPCParameters *rpcParams)
                {
                    RakServerInterface *pRakServer = server::GetServerInstance()->getRakServer();
                    CPool<CPlayer> *pPlayerPool = server::GetServerInstance()->GetNetGame()->GetPlayerPool();
                    event::EventPool *pEventPool = server::GetServerInstance()->getEventPool();

                    char *Data = reinterpret_cast<char *>(rpcParams->input);
                    int iBitLength = rpcParams->numberOfBitsOfData;
                    RakNet::BitStream bsData((unsigned char *)Data, (iBitLength / 8) + 1, false);

                    WORD playerId = (WORD)pRakServer->GetIndexFromPlayerID(rpcParams->sender);
                    char szText[256];
                    int iTextLen;

                    memset(szText, 0, 256);

                    bsData.Read(iTextLen);
                    bsData.Read((char *)szText, iTextLen);
                    szText[iTextLen] = '\0';
                    std::cout << szText << "\n";

                    // OnPlayerMessage
                    event::OnPlayerCommandText_params params;
                    params.player = pPlayerPool->GetAt(playerId);
                    params.cmd = szText;
                    pEventPool->Emit(event::SERVER_EVENT_COMMANDTEXT, static_cast<void *>(&params));
                }
            }
        }
    }
}
