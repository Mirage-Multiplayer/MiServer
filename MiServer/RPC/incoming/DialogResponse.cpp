#include <MiServer/RPC/RPC.hpp>
#include <MiServer/RPC/RPCList.hpp>
#include <MiRak/RakServer.h>
#include <MiRak/BitStream.h>
#include <MiServer/server/Server.hpp>
#include <MiServer/server/ServerInstance.hpp>
#include <MiServer/MiServer.hpp>
#include <MiServer/player/defines.hpp>
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
					mimp::internal::player::PlayerPool *pPlayerPool = internal::server::GetServerInstance()->getPlayerPool();

					char *Data = reinterpret_cast<char *>(rpcParams->input);
					int iBitLength = rpcParams->numberOfBitsOfData;
					PlayerID sender = rpcParams->sender;

					RakNet::BitStream bsData((unsigned char *)Data, (iBitLength / 8) + 1, false);
					PLAYERID playerID = pRakServer->GetIndexFromPlayerID(sender);

					if (!pPlayerPool->IsPlayerConnected(playerID))
						return;

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
