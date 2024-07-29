#include "RPC/RPC.hpp"

namespace mimp {
    namespace internal {
        namespace RPC {
            namespace incomming {
				void DialogResponse(RPCParameters* rpcParams)
				{
					RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
					mimp::internal::player::PlayerPool* pPlayerPool = internal::server::GetServerInstance()->getPlayerPool();

					PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
					int iBitLength = rpcParams->numberOfBitsOfData;
					PlayerID sender = rpcParams->sender;

					RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);
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
