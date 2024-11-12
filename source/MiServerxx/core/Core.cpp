#include <MiServerxx/MiServerxx.hpp>
#include <iostream>
#include <thread>
#include <MiRak/RakNetworkFactory.h>
#include <MiRak/PacketEnumerations.h>
#include <MiRak/RakEncr.h>
#include <MiServerxx/core/Core.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/event/EventPool.hpp>
#include <MiServerxx/packet/PlayerSync.hpp>
#include <MiServerxx/packet/AimSync.hpp>
#include <MiServerxx/packet/BulletSync.hpp>
#include <MiServerxx/packet/PassengerSync.hpp>
#include <MiServerxx/packet/UnoccupiedSync.hpp>
#include <MiServerxx/packet/VehicleSync.hpp>
#include <MiServerxx/netgame/NetGame.hpp>
#include <MiServerxx/RPC/RPCList.hpp>
#include <MiServerxx/config.h>

mimp::ServerInfo::ServerInfo(const char *hostname, const char *gamemode, const char *lang, const unsigned int max_players) : hostname(hostname), gamemode(gamemode), lang(lang), max_players(max_players)
{
}

mimp::CCore::CCore(const ServerInfo &info) : m_info(info),
											 m_port(0),
											 m_initialized(false)
{
	this->m_pNetGame = new mimp::CNetGame(info.max_players, 6000);
	this->m_pEventPool = new internal::event::CEventPool();
	this->m_pRakServer = RakNetworkFactory::GetRakServerInterface();
}

mimp::CCore::CCore(const ServerInfo &info, const ServerConfig &config) : m_info(info),
																		 m_port(0),
																		 m_initialized(false),
																		 m_cfg(config)
{
	this->m_pNetGame = new mimp::CNetGame(info.max_players, 6000);
	this->m_pEventPool = new internal::event::CEventPool();
	this->m_pRakServer = RakNetworkFactory::GetRakServerInterface();
	this->LoadEvents();
}

mimp::CCore::~CCore()
{
	this->m_pRakServer->Disconnect(300);
	RakNetworkFactory::DestroyRakServerInterface(this->m_pRakServer);

	delete this->m_pNetGame;
	delete this->m_pEventPool;
}

int mimp::CCore::Run(uint16_t port)
{
	std::cout << "[Mi:MP] Initializing Mi:MP Server instance version " << __MISERVER_VERSION << "\n";

	if (internal::server::GetCoreInstance() != nullptr)
	{
		std::cout << "[Mi:MP] Server instance already Loaded!. Aborting...";
		return -1;
	}
	this->m_port = port;

	srand((unsigned int)time(NULL));
	RakNet::RakEncr::m_srvChallenge = (unsigned int)rand();
	RakNet::RakEncr::setPort(port);

	this->m_pRakServer->Start(this->m_info.max_players, 0, 5, port);
	this->m_pRakServer->StartOccasionalPing();

	internal::server::SetCoreInstance(this);
	this->LoadRPCs();
	this->RegisterRPCs();
	// internal::RPC::RegisterServerRPCs(this->m_pRakServer);

	this->m_initialized = true;
	std::cout << "[Mi:MP] Successfully initialized Mi:MP ' Mi-Server " << __MISERVER_VERSION << " ' \n";
	MIMP_GET_EVENT(SERVERINIT, this->m_pEventPool)
		SERVERINIT->Emit();

	return 1;
}

int mimp::CCore::Shutdown(void)
{
	this->m_pRakServer->Disconnect(300);

	this->m_pNetGame->Clear();
	this->m_pEventPool->Clear();

	this->m_port = 0;

	RakNet::RakEncr::m_srvChallenge = 0;
	RakNet::RakEncr::setPort(0);

	internal::server::SetCoreInstance(nullptr);

	return 1;
}

int mimp::CCore::ProccessTick(void)
{
	unsigned char packetIdentifier;
	Packet *pkt = nullptr;
	while ((pkt = this->m_pRakServer->Receive()))
	{
		if ((unsigned char)pkt->data[0] == ID_TIMESTAMP)
		{
			if (pkt->length > sizeof(unsigned char) + sizeof(unsigned int))
			{

				packetIdentifier = (unsigned char)pkt->data[sizeof(unsigned char) + sizeof(unsigned int)];
			}
			else
			{
				return 1;
			}
		}
		else
			packetIdentifier = (unsigned char)pkt->data[0];

		WORD playerID = pkt->playerIndex;
		switch (packetIdentifier)
		{
		case ID_DISCONNECTION_NOTIFICATION:
		{
			this->m_pNetGame->GetPlayerPool()->DeleteAt(playerID);
			break;
		}
		case ID_NEW_INCOMING_CONNECTION:
		{
			break;
		}
		case ID_CONNECTION_LOST:
		{
			this->m_pNetGame->GetPlayerPool()->DeleteAt(playerID);
			break;
		}
		case ID_PLAYER_SYNC:
		{
			mimp::internal::packet::PlayerSync(pkt);
			break;
		}
		case ID_AIM_SYNC:
		{
			mimp::internal::packet::AimSync(pkt);
			break;
		}
		case ID_BULLET_SYNC:
		{
			mimp::internal::packet::BulletSync(pkt);
			break;
		}
		case ID_VEHICLE_SYNC:
		{
			mimp::internal::packet::VehicleSync(pkt);
			break;
		}
		case ID_UNOCCUPIED_SYNC:
		{
			mimp::internal::packet::UnoccupiedSync(pkt);
			break;
		}
		}
		this->m_pRakServer->DeallocatePacket(pkt);
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(5));
	return 1;
}

void mimp::CCore::LoadEvents(void) {
	/*
	enum
			{
				SERVER_EVENT_SERVERINIT = 0,
				SERVER_EVENT_SERVEREXIT = 1,
				SERVER_EVENT_PLAYERCONNECT,
				SERVER_EVENT_PLAYERDISCONNECT,
				SERVER_EVENT_PLAYERSPAWN,
				SERVER_EVENT_PLAYERDEATH,
				SERVER_EVENT_PLAYERTEXT,
				SERVER_EVENT_COMMANDTEXT,
				SERVER_EVENT_PLAYERUPDATE
			};
	*/

	auto serverinit = std::make_unique<mimp::internal::event::SERVER_EVENT_SERVERINIT_T>();
	auto serverexit = std::make_unique<mimp::internal::event::SERVER_EVENT_SERVEREXIT_T>();
	auto playerconnect = std::make_unique<mimp::internal::event::SERVER_EVENT_PLAYERCONNECT_T>();
	auto playerdisconnect = std::make_unique<mimp::internal::event::SERVER_EVENT_PLAYERDISCONNECT_T>();
	auto playerspawn = std::make_unique<mimp::internal::event::SERVER_EVENT_PLAYERSPAWN_T>();
	auto playerdeath = std::make_unique<mimp::internal::event::SERVER_EVENT_PLAYERDEATH_T>();
	auto playertxt = std::make_unique<mimp::internal::event::SERVER_EVENT_PLAYERTEXT_T>();
	auto commandtxt = std::make_unique<mimp::internal::event::SERVER_EVENT_COMMANDTEXT_T>();
	auto playerupdate = std::make_unique<mimp::internal::event::SERVER_EVENT_PLAYERUPDATE_T>();

	this->m_pEventPool->RegisterEvent(mimp::internal::event::SERVER_EVENT_SERVERINIT, std::move(serverinit));
	this->m_pEventPool->RegisterEvent(mimp::internal::event::SERVER_EVENT_SERVEREXIT, std::move(serverexit));
	this->m_pEventPool->RegisterEvent(mimp::internal::event::SERVER_EVENT_PLAYERCONNECT, std::move(playerconnect));
	this->m_pEventPool->RegisterEvent(mimp::internal::event::SERVER_EVENT_PLAYERDISCONNECT, std::move(playerdisconnect));
	this->m_pEventPool->RegisterEvent(mimp::internal::event::SERVER_EVENT_PLAYERSPAWN, std::move(playerspawn));
	this->m_pEventPool->RegisterEvent(mimp::internal::event::SERVER_EVENT_PLAYERDEATH, std::move(playerdeath));
	this->m_pEventPool->RegisterEvent(mimp::internal::event::SERVER_EVENT_PLAYERTEXT, std::move(playertxt));
	this->m_pEventPool->RegisterEvent(mimp::internal::event::SERVER_EVENT_COMMANDTEXT, std::move(commandtxt));
	this->m_pEventPool->RegisterEvent(mimp::internal::event::SERVER_EVENT_PLAYERUPDATE, std::move(playerupdate));

}


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

	for (const auto& rpc : this->m_RPCs) {
		int uid = rpc.first;
		this->m_pRakServer->RegisterAsRemoteProcedureCall(&uid, [uid, this](RPCParameters* params) -> void {
			this->GetRPCHandler(uid)->Call(params);
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
