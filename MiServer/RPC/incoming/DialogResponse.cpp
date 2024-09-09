#include <MiServer/RPC/RPC.hpp>
#include <MiServer/RPC/RPCList.hpp>
#include <MiRak/RakServer.h>
#include <MiRak/BitStream.h>
#include <MiServer/server/Server.hpp>
#include <MiServer/server/ServerInstance.hpp>
#include <MiServer/MiServer.hpp>
#include <MiServer/netgame/NetGame.hpp>
namespace mimp
{
	namespace internal
	{
		namespace RPC
		{
			namespace incoming
			{
				void Handler::DialogResponse(RPCParameters *rpcParams)
				{
					RakServerInterface *pRakServer = internal::server::GetServerInstance()->getRakServer();
					CPool<CPlayer> *pPlayerPool = internal::server::GetServerInstance()->GetNetGame()->GetPlayerPool();

					char *Data = reinterpret_cast<char *>(rpcParams->input);
					int iBitLength = rpcParams->numberOfBitsOfData;
					PlayerID sender = rpcParams->sender;

					RakNet::BitStream bsData((unsigned char *)Data, (iBitLength / 8) + 1, false);
					WORD playerID = pRakServer->GetIndexFromPlayerID(sender);

					if (pPlayerPool->GetAt(playerID) == nullptr)
					{
						return;
					}

					WORD wDialogID;
					BYTE bButtonID;
					WORD wListBoxItem;
					char szInputResp[128 + 1];
					unsigned char iInputRespLen;

					bsData.Read(wDialogID);
					bsData.Read(bButtonID);
					bsData.Read(wListBoxItem);
					bsData.Read(iInputRespLen);
					bsData.Read(szInputResp, iInputRespLen);
					szInputResp[iInputRespLen] = 0;

					// OnDialogResponse
				}

			}
		}
	}
}
