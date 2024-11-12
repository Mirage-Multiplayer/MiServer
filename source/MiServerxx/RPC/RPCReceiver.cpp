#include <MiServerxx/RPC/RPCReceiver.hpp>

using namespace mimp::internal::RPC;

static void EnterVehicle(RPCParameters* rpcParams);
static void ExitVehicle(RPCParameters* rpcParams);
static void VehicleDamaged(RPCParameters* rpcParams);
static void ScmEvent(RPCParameters* rpcParams);
static void VehicleDestroyed(RPCParameters* rpcParams);
static void SendSpawn(RPCParameters* rpcParams);
static void ChatMessage(RPCParameters* rpcParams);
static void InteriorChangeNotification(RPCParameters* rpcParams);
static void DeathNotification(RPCParameters* rpcParams);
static void SendCommand(RPCParameters* rpcParams);
static void ClickPlayer(RPCParameters* rpcParams);
static void DialogResponse(RPCParameters* rpcParams);
static void ClientCheckResponse(RPCParameters* rpcParams);
static void GiveTakeDamage(RPCParameters* rpcParams);
static void GiveActorDamage(RPCParameters* rpcParams);
static void MapMarker(RPCParameters* rpcParams);
static void RequestClass(RPCParameters* rpcParams);
static void RequestSpawn(RPCParameters* rpcParams);
static void MenuSelect(RPCParameters* rpcParams);
static void MenuQuit(RPCParameters* rpcParams);
static void SelectTextDraw(RPCParameters* rpcParams);
static void PickedUpPickup(RPCParameters* rpcParams);
static void SelectObject(RPCParameters* rpcParams);
static void EditAttachedObject(RPCParameters* rpcParams);
static void EditObject(RPCParameters* rpcParams);
static void UpdateScoresAndPings(RPCParameters* rpcParams);
static void ClientJoin(RPCParameters* rpcParams);
static void NPCJoin(RPCParameters* rpcParams);
static void CameraTarget(RPCParameters* rpcParams);
static void HandleUnsupported(RPCParameters* rpcParams);

RPCReceiver::RPCReceiver(bool useDefault) {

}

std::vector<RPCReceiver::fn> RPCReceiver::GetHandlers(const int rpcid) {
	return this->m_RPCMap.at(rpcid);
}

const bool RPCReceiver::hasHandler(const int rpcid) {
	return (this->m_RPCMap.at(rpcid).size() != 0);
}

const bool RPCReceiver::hasRPC(const int rpcid) {
	if (this->m_RPCMap.find(rpcid) != this->m_RPCMap.end())
	{
		return true;
	}
	else {
		return false;
	}
}

void RPCReceiver::OnRPC(const int rpcid, std::function<void(RPCParameters* params)> handler) {
	this->m_RPCMap.at(rpcid).push_back(handler);
}
