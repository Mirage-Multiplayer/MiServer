#include <MiServerxx/MiServerxx.hpp>
#include <MiServerxx/RPC/RPC.hpp>
#include <MiServerxx/RPC/RPCList.hpp>
#include <MiServerxx/server/Server.hpp>
#include <MiServerxx/server/ServerInstance.hpp>
#include <MiServerxx/event/EventTypes.hpp>
#include <MiServerxx/event/EventPool.hpp>
#include <MiServerxx/netgame/NetGame.hpp>

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
					CPool<CPlayer> *pPlayerPool = server::GetServerInstance()->GetNetGame()->GetPlayerPool();
					event::CEventPool *pEventPool = server::GetServerInstance()->getEventPool();

					char *Data = reinterpret_cast<char *>(rpcParams->input);
					int iBitLength = rpcParams->numberOfBitsOfData;
					RakNet::BitStream bsData((unsigned char *)Data, (iBitLength / 8) + 1, false);

					WORD playerId = (WORD)pRakServer->GetIndexFromPlayerID(rpcParams->sender);
					char szText[256];
					BYTE byteTextLen;

					memset(szText, 0, 256);

					bsData.Read(byteTextLen);
					bsData.Read((char *)szText, byteTextLen);
					szText[byteTextLen] = '\0';

					// OnPlayerMessage
					event::OnPlayerText_params params;
					params.player = pPlayerPool->GetAt(playerId);
					params.text = szText;
					pEventPool->Emit(event::SERVER_EVENT_PLAYERTEXT, static_cast<void *>(&params));
				}
			}
		}
	}
}
