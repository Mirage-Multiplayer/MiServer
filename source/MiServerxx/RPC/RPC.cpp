#include <MiRak/BitStream.h>
#include <MiRak/RakEncr.h>
#include <string>
#include <thread>
#include <MiServerxx/core/Core.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/MiServerxx.hpp>
#include <MiServerxx/types.h>
#include <MiServerxx/RPC/RPCList.hpp>
#include <MiServerxx/RPC/RPC.hpp>

#include <MiServerxx/packet/SyncData.hpp>
#include <MiServerxx/packet/defines.hpp>
#include <MiServerxx/netgame/NetGame.hpp>

namespace mimp
{
	namespace internal
	{
		namespace RPC
		{
			IRPC::IRPC(const int UID): m_UID(UID) {

			}

			void IRPC::addHandler(fn handler) {
				this->m_handlers.push_back(handler);
			}

			bool IRPC::hasHandler(void) {
				return (this->m_handlers.size() != 0);
			}

			void IRPC::Call(RPCParameters* params) {
				for (auto& handler : this->m_handlers) {
					handler(params);
				}
			}

			/*
			void InitGameForPlayer(WORD playerID)
			{
				mimp::CCore *svr = mimp::internal::server::GetCoreInstance();

				// TODO: Modify server config
				RakNet::BitStream bsInitGame;
				bsInitGame.WriteCompressed((bool)1); // m_bZoneNames
				bsInitGame.WriteCompressed((bool)1); // m_bUseCJWalk
				bsInitGame.WriteCompressed((bool)1); // m_bAllowWeapons
				bsInitGame.WriteCompressed((bool)0); // m_bLimitGlobalChatRadius
				bsInitGame.Write((float)200.00f);	 // m_fGlobalChatRadius
				bsInitGame.WriteCompressed((bool)0); // bStuntBonus
				bsInitGame.Write((float)70.0f);		 // m_fNameTagDrawDistance
				bsInitGame.WriteCompressed((bool)0); // m_bDisableEnterExits
				bsInitGame.WriteCompressed((bool)1); // m_bNameTagLOS
				bsInitGame.WriteCompressed((bool)0); // m_bManualVehicleEngineAndLight
				bsInitGame.Write((int)1);			 // m_iSpawnsAvailable
				bsInitGame.Write(playerID);			 // MyPlayerID
				bsInitGame.WriteCompressed((bool)1); // m_bShowPlayerTags
				bsInitGame.Write((int)1);			 // m_iShowPlayerMarkers
				bsInitGame.Write((BYTE)12);			 // m_byteWorldTime
				bsInitGame.Write((BYTE)10);			 // m_byteWeather
				bsInitGame.Write((float)m_fGravity); // m_fGravity
				bsInitGame.WriteCompressed((bool)0); // bLanMode
				bsInitGame.Write((int)0);			 // m_iDeathDropMoney
				bsInitGame.WriteCompressed((bool)0); // m_bInstagib

				bsInitGame.Write((int)40); // iNetModeNormalOnfootSendRate
				bsInitGame.Write((int)40); // iNetModeNormalIncarSendRate
				bsInitGame.Write((int)40); // iNetModeFiringSendRate
				bsInitGame.Write((int)10); // iNetModeSendMultiplier

				bsInitGame.Write((BYTE)iLagCompensation); // m_bLagCompensation

				bsInitGame.Write((BYTE)0); // unknown
				bsInitGame.Write((BYTE)0); // unknown
				bsInitGame.Write((BYTE)0); // unknown

				BYTE bServerNameLen = (BYTE)strlen(svr->getInfo().hostname.c_str());
				bsInitGame.Write(bServerNameLen);
				bsInitGame.Write(svr->getInfo().hostname.c_str(), bServerNameLen);

				BYTE vehModels[212];
				memset(vehModels, 1, 212);
				bsInitGame.Write((char *)&vehModels, 212);

				svr->getRakServer()->RPC(&outgoing::RPC_InitGame, &bsInitGame, HIGH_PRIORITY, RELIABLE,
										 0, svr->getRakServer()->GetPlayerIDFromIndex(playerID), FALSE, FALSE, UNASSIGNED_NETWORK_ID, NULL);
			}
			*/

			
		}
	}
}
