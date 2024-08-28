#include <MiServer/MiServer.hpp>
#include <MiServer/RPC/RPC.hpp>
#include <MiServer/RPC/RPCList.hpp>
#include <MiServer/server/Server.hpp>
#include <MiServer/server/ServerInstance.hpp>
#include <MiServer/event/EventTypes.hpp>
#include <MiServer/event/EventPool.hpp>
#include <MiServer/player/PlayerPool.hpp>
#include <MiServer/player/Player.hpp>

namespace mimp
{
	namespace internal
	{
		namespace RPC
		{
			namespace incoming
			{
				void Handler::ChatMessage(RPCParameters *rpcParams)
				{
					RakServerInterface *pRakServer = server::GetServerInstance()->getRakServer();
					player::PlayerPool *pPlayerPool = server::GetServerInstance()->getPlayerPool();
					event::EventPool *pEventPool = server::GetServerInstance()->getEventPool();

					char *Data = reinterpret_cast<char *>(rpcParams->input);
					int iBitLength = rpcParams->numberOfBitsOfData;
					RakNet::BitStream bsData((unsigned char *)Data, (iBitLength / 8) + 1, false);

					PLAYERID playerId = (PLAYERID)pRakServer->GetIndexFromPlayerID(rpcParams->sender);
					char szText[256];
					BYTE byteTextLen;

					memset(szText, 0, 256);

					bsData.Read(byteTextLen);
					bsData.Read((char *)szText, byteTextLen);
					szText[byteTextLen] = '\0';

					// OnPlayerMessage
					event::OnPlayerText_params params;
					params.player = pPlayerPool->Get(playerId);
					params.text = szText;
					pEventPool->Emit(event::SERVER_EVENT_PLAYERTEXT, static_cast<void *>(&params));
				}
			}
		}
	}
}
