#ifndef __MISERVER_RPC_HPP
#define __MISERVER_RPC_HPP
#include <MiRak/BitStream.h>
#include <MiRak/RakEncr.h>
#include <MiRak/RakServer.h>
#include <MiServer/player/PlayerTypes.hpp>

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
			void InitGameForPlayer(PLAYERID playerID);
			void SendPlayerPoolToPlayer(PLAYERID playerID);
			void SpawnAllVehiclesForPlayer(PLAYERID playerID);
			void RegisterServerRPCs(RakServerInterface *pRakServer);
			void UnRegisterServerRPCs(RakServerInterface *pRakServer);
		}
	}
}

#endif
