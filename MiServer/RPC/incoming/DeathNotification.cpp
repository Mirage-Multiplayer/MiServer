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
				void Handler::DeathNotification(RPCParameters *rpcParams)
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

					unsigned char ReasonID;
					unsigned short KillerID;

					bsData.Read(ReasonID);
					bsData.Read(KillerID);

					if (KillerID != 0xFFFF)
					{
						if (KillerID < 0 || KillerID >= pPlayerPool->GetMax())
							return;

						if (pPlayerPool->GetAt(KillerID) == nullptr)
						{
							return;
						}

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
