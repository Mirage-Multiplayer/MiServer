#include "RPC/RPC.hpp"

namespace mimp {
    namespace internal {
        namespace RPC {
            namespace incomming {
				void RequestClass(RPCParameters* rpcParams)
				{
					PCHAR Data = reinterpret_cast<PCHAR>(rpcParams->input);
					int iBitLength = rpcParams->numberOfBitsOfData;

					RakNet::BitStream bsData((unsigned char*)Data, (iBitLength / 8) + 1, false);

					int iClass;
					bsData.Read(iClass);

					mimp::internal::packet::PLAYER_SPAWN_INFO psInfo;
					memset(&psInfo, 0, sizeof(psInfo));
					psInfo.byteTeam = 0xFF;
					psInfo.iSkin = 33;
					psInfo.vecPos[0] = 389.8672f;
					psInfo.vecPos[1] = 2543.0046f;
					psInfo.vecPos[2] = 16.5391f;
					psInfo.fRotation = 90.0f;
					psInfo.iSpawnWeapons[0] = 38;
					psInfo.iSpawnWeaponsAmmo[0] = 69;

					// OnPlayerRequestClass


					RakNet::BitStream bsReply;
					bsReply.Write((BYTE)1);
					bsReply.Write((char*)&psInfo, sizeof(psInfo));
					RakServerInterface* pRakServer = internal::server::GetServerInstance()->getRakServer();
					pRakServer->RPC(&RPC_RequestClass, &bsReply, HIGH_PRIORITY, RELIABLE,
						0, rpcParams->sender, FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
				}
            }
        }
    }
}
