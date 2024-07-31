#include "RPC/RPC.hpp"
#include "server/ServerInstance.hpp"
#include "player/defines.hpp"

namespace mimp {
    namespace internal {
        namespace RPC {
            namespace incomming {
				void Handler::DeathNotification(RPCParameters* rpcParams)
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

					unsigned char ReasonID;
					unsigned short KillerID;

					bsData.Read(ReasonID);
					bsData.Read(KillerID);

					if (KillerID != 0xFFFF)
					{
						if (KillerID < 0 || KillerID >= MAX_PLAYERS)
							return;

						if (!pPlayerPool->IsPlayerConnected(KillerID))
							return;

						if (ReasonID == 46 || ReasonID == 48 || ReasonID == 49)
							return;
					}

					RakNet::BitStream bsDeath;

					bsDeath.Write((unsigned short)playerID);
					pRakServer->RPC(&outgoing::RPC_DeathBroadcast, &bsDeath, HIGH_PRIORITY, RELIABLE_ORDERED, 0, pRakServer->GetPlayerIDFromIndex(playerID), TRUE, FALSE, UNASSIGNED_NETWORK_ID, NULL);

					// OnPlayerDeath
				}
            }
        }
    }
}
