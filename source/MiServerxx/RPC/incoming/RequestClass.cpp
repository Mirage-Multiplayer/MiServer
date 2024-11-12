#include <MiServerxx/RPC/RPC.hpp>
#include <MiServerxx/RPC/RPCList.hpp>
#include <MiRak/RakServer.h>
#include <MiRak/BitStream.h>
#include <MiServerxx/core/Core.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/MiServerxx.hpp>

using namespace mimp;
using namespace mimp::internal;
using namespace mimp::internal::RPC;
void IRPCFunc_RequestClass(RPCParameters* rpcParams)
{
	char* Data = reinterpret_cast<char*>(rpcParams->input);
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

	RakServerInterface* pRakServer = internal::server::GetCoreInstance()->getRakServer();
	// OnPlayerRequestClass

	ORPCRequestClass rpc;
	rpc.bRequestResponse = 1;
	rpc.byteTeam = 0xFF;
	rpc.dSkin = 33;
	rpc.X = 389.8672f;
	rpc.Y = 2543.0046f;
	rpc.Z = 16.5391f;
	rpc.fRotation = 90.0f;
	rpc.dSpawnWeapons1 = 38;
	rpc.dSpawnWeaponsAmmo1 = 69;
	server::GetCoreInstance()->SendRPC(pRakServer->GetIndexFromPlayerID(rpcParams->sender), &rpc);
}
