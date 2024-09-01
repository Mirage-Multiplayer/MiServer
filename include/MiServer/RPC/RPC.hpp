#ifndef __MISERVER_RPC_HPP
#define __MISERVER_RPC_HPP
#include <MiRak/BitStream.h>
#include <MiRak/RakEncr.h>
#include <MiRak/RakServer.h>
#include <MiServer/types.h>

#define REJECT_REASON_BAD_VERSION 1
#define REJECT_REASON_BAD_NICKNAME 2
#define REJECT_REASON_BAD_MOD 3
#define REJECT_REASON_BAD_PLAYERID 4

namespace mimp
{
	namespace internal
	{
		namespace RPC
		{
			extern float m_fGravity;
			extern int iLagCompensation;
			void InitGameForPlayer(WORD playerID);
			void SendPlayerPoolToPlayer(WORD playerID);
			void SpawnAllVehiclesForPlayer(WORD playerID);
			void RegisterServerRPCs(RakServerInterface *pRakServer);
			void UnRegisterServerRPCs(RakServerInterface *pRakServer);
		}
	}
}

#endif
