#include <MiServerxx/RPC/RPC.hpp>
#include <MiServerxx/RPC/RPCList.hpp>
#include <MiRak/RakServer.h>
#include <MiRak/BitStream.h>
#include <MiServerxx/core/Core.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/MiServerxx.hpp>
#include <MiServerxx/netgame/NetGame.hpp>

using namespace mimp;
using namespace mimp::internal;
using namespace mimp::internal::RPC;
void IRPCFunc_SendSpawn(RPCParameters* rpcParams)
{
	RakServerInterface* pRakServer = internal::server::GetCoreInstance()->getRakServer();
	CPool<CPlayer>* pPlayerPool = internal::server::GetCoreInstance()->GetNetGame()->GetPlayerPool();
	WORD playerId = (WORD)pRakServer->GetIndexFromPlayerID(rpcParams->sender);
	BYTE byteFightingStyle = 4;
	BYTE byteTeam = -1;
	int iSkin = 0;
	float vecPos[3] = { 389.8672f, 2543.0046f, 16.5391f };
	float fRotation = 90.0f;
	DWORD dwColor = -1;

	if (pPlayerPool->GetAt(playerId) == nullptr)
	{
		return;
	}

	mimp::CPlayer* pPlayer = pPlayerPool->GetAt(playerId);
	if (pPlayer == nullptr)
	{
		// Invalid player, usually not connected.
		return;
	}


	MIMP_GET_EVENT(PLAYERSPAWN, internal::server::GetCoreInstance()->getEventPool())
		PLAYERSPAWN->Emit(pPlayer);

	ORPCWorldPlayerAdd rpc;
	rpc.wPlayerID = playerId;
	rpc.dSkinId = iSkin;
	rpc.team = byteTeam;
	rpc.PosX = vecPos[0];
	rpc.PosY = vecPos[1];
	rpc.PosZ = vecPos[2];
	rpc.facing_angle = fRotation;
	rpc.player_color = dwColor;
	rpc.fighting_style = byteFightingStyle;
	server::GetCoreInstance()->BroadcastRPC(&rpc, playerId);
}
