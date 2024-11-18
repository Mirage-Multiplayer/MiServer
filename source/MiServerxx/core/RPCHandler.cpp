#pragma once

#include <MiServerxx/core/Core.hpp>

void IRPCFunc_Unsuported(RPCParameters* rpcParams) {
	std::cout << "[Mi:MP] Unsuported RPC Call\n";
}

#define UNSUPORTED_RPC(name,id) \
	mimp::internal::RPC::IRPC_##name = new mimp::internal::RPC::IRPC(id); \
	mimp::internal::RPC::IRPC_##name->addHandler(IRPCFunc_Unsuported); \
	this->RegisterRPC(mimp::internal::RPC::IRPC_##name);

#define LOAD_RPC(name,id) \
	extern void IRPCFunc_##name(RPCParameters*); \
	mimp::internal::RPC::IRPC_##name = new mimp::internal::RPC::IRPC(id); \
	mimp::internal::RPC::IRPC_##name->addHandler(IRPCFunc_##name); \
	this->RegisterRPC(mimp::internal::RPC::IRPC_##name);


void mimp::CCore::LoadRPCs(void) {
	//using namespace mimp::internal::RPC;

	LOAD_RPC(EnterVehicle, 26);
	LOAD_RPC(ExitVehicle, 154);
	LOAD_RPC(VehicleDamaged, 106);
	LOAD_RPC(ScmEvent, 96);
	UNSUPORTED_RPC(VehicleDestroyed, 136);
	LOAD_RPC(SendSpawn, 52);
	LOAD_RPC(ChatMessage, 101);
	LOAD_RPC(InteriorChangeNotification, 118);
	LOAD_RPC(DeathNotification, 53);
	LOAD_RPC(SendCommand, 50);
	UNSUPORTED_RPC(ClickPlayer, 23);
	LOAD_RPC(DialogResponse, 62);
	UNSUPORTED_RPC(ClientCheckResponse, 103);
	UNSUPORTED_RPC(GiveTakeDamage, 115);
	UNSUPORTED_RPC(GiveActorDamage, 177);
	UNSUPORTED_RPC(MapMarker, 119);
	LOAD_RPC(RequestClass, 128);
	LOAD_RPC(RequestSpawn, 129);
	UNSUPORTED_RPC(MenuQuit, 140);
	UNSUPORTED_RPC(MenuSelect, 132);
	UNSUPORTED_RPC(SelectTextDraw, 83);
	UNSUPORTED_RPC(PickedUpPickup, 131);
	UNSUPORTED_RPC(SelectObject, 27);
	UNSUPORTED_RPC(EditAttachedObject, 116);
	UNSUPORTED_RPC(EditObject, 117);
	LOAD_RPC(UpdateScoresAndPings, 155);
	LOAD_RPC(ClientJoin, 25);
	UNSUPORTED_RPC(NPCJoin, 54);
	UNSUPORTED_RPC(CameraTarget, 168);
}

void mimp::CCore::SendRPC(const int playerid, mimp::internal::RPC::ORPC* rpc) {
	RakNet::BitStream bs;
	int uid = rpc->GetUID();
	rpc->Write(&bs);
	this->m_pRakServer->RPC(&uid, &bs, HIGH_PRIORITY, RELIABLE, 0, this->m_pRakServer->GetPlayerIDFromIndex(playerid), false, false, UNASSIGNED_NETWORK_ID, nullptr);
}

void mimp::CCore::BroadcastRPC(mimp::internal::RPC::ORPC* rpc) {
	RakNet::BitStream bs;
	int uid = rpc->GetUID();
	rpc->Write(&bs);
	this->m_pRakServer->RPC(&uid, &bs, HIGH_PRIORITY, RELIABLE, 0, UNASSIGNED_PLAYER_ID, true, false, UNASSIGNED_NETWORK_ID, nullptr);
}

void mimp::CCore::BroadcastRPC(mimp::internal::RPC::ORPC* rpc, const int playerid) {
	RakNet::BitStream bs;
	int uid = rpc->GetUID();
	rpc->Write(&bs);
	this->m_pRakServer->RPC(&uid, &bs, HIGH_PRIORITY, RELIABLE, 0, this->m_pRakServer->GetPlayerIDFromIndex(playerid), true, false, UNASSIGNED_NETWORK_ID, nullptr);
}

bool mimp::CCore::RegisterRPC(internal::RPC::IRPC* rpc) {
	const int uid = rpc->GetUID();
	if (this->m_RPCs.find(uid) != this->m_RPCs.end()) {
		return false;
	}
	this->m_RPCs[uid] = rpc;
	return true;
}

mimp::internal::RPC::IRPC* mimp::CCore::GetRPCHandler(const int rpcid) {
	return this->m_RPCs.at(rpcid);
}

void mimp::CCore::UnregisterRPC(const int rpcid) {
	delete this->m_RPCs[rpcid];
	this->m_RPCs[rpcid] = nullptr;
}


void mimp::CCore::RegisterRPCs(void) {
	using namespace mimp::internal::RPC;

	for (const auto& pair : this->m_RPCs) {
		int uid = pair.first;
		auto rpc = pair.second;
		this->m_pRakServer->RegisterAsRemoteProcedureCall(&uid, [rpc](RPCParameters* params) -> void {
			rpc->Call(params);
			});
	}

	/*
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_ClientJoin.GetUID(), IRPC_ClientJoin.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_RequestClass.GetUID(), IRPC_RequestClass.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_RequestSpawn.GetUID(), IRPC_RequestSpawn.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_SendSpawn.GetUID(), IRPC_SendSpawn.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_ChatMessage.GetUID(), IRPC_ChatMessage.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_UpdateScoresAndPings.GetUID(), IRPC_UpdateScoresAndPings.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_VehicleDamaged.GetUID(), IRPC_VehicleDamaged.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_EnterVehicle.GetUID(), IRPC_EnterVehicle.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_ExitVehicle.GetUID(), IRPC_ExitVehicle.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_DeathNotification.GetUID(), IRPC_DeathNotification.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_DialogResponse.GetUID(), IRPC_DialogResponse.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_InteriorChangeNotification.GetUID(), IRPC_InteriorChangeNotification.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_ScmEvent.GetUID(), IRPC_ScmEvent.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_SendCommand.GetUID(), IRPC_SendCommand.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_CameraTarget.GetUID(), IRPC_Unsupported.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_ClickPlayer.GetUID(), IRPC_Unsupported.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_ClientCheckResponse.GetUID(), IRPC_Unsupported.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_VehicleDestroyed.GetUID(), IRPC_Unsupported.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_EditAttachedObject.GetUID(), IRPC_Unsupported.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_EditObject.GetUID(), IRPC_Unsupported.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_GiveActorDamage.GetUID(), IRPC_Unsupported.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_GiveTakeDamage.GetUID(), IRPC_GiveTakeDamage.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_MapMarker.GetUID(), IRPC_Unsupported.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_MenuQuit.GetUID(), IRPC_Unsupported.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_NPCJoin.GetUID(), IRPC_Unsupported.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_PickedUpPickup.GetUID(), IRPC_Unsupported.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_SelectObject.GetUID(), IRPC_Unsupported.GetHandler());
	this->m_pRakServer->RegisterAsRemoteProcedureCall(&IRPC_SelectTextDraw.GetUID(), IRPC_Unsupported.GetHandler());
	*/
}

