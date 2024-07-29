#include "RPC/RPC.hpp"

namespace mimp {
    namespace internal {
        namespace RPC {
            namespace incomming {
				void ChatMessage(RPCParameters* rpcParams)
				{
					RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();

					PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
					int iBitLength = rpcParams->numberOfBitsOfData;
					RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);

					PLAYERID playerId = (PLAYERID)pRakServer->GetIndexFromPlayerID(rpcParams->sender);
					char szText[256];
					BYTE byteTextLen;

					memset(szText, 0, 256);

					bsData.Read(byteTextLen);
					bsData.Read((char*)szText, byteTextLen);
					szText[byteTextLen] = '\0';

					// OnPlayerMessage

				}
            }
        }
    }
}
