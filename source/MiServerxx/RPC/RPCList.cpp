#include <MiServerxx/RPC/RPC.hpp>

namespace mimp {
	namespace internal {
		namespace RPC {
			IRPC* IRPC_EnterVehicle = nullptr; // 26
			IRPC* IRPC_ExitVehicle = nullptr;	// 154
			IRPC* IRPC_VehicleDamaged = nullptr; // 106
			IRPC* IRPC_ScmEvent = nullptr; // 96
			IRPC* IRPC_VehicleDestroyed = nullptr; // 136
			IRPC* IRPC_SendSpawn = nullptr; // 52
			IRPC* IRPC_ChatMessage = nullptr; // 101
			IRPC* IRPC_InteriorChangeNotification = nullptr; // 118
			IRPC* IRPC_DeathNotification = nullptr; // 53
			IRPC* IRPC_SendCommand = nullptr; // 50
			IRPC* IRPC_ClickPlayer = nullptr; // 23
			IRPC* IRPC_DialogResponse = nullptr; // 62
			IRPC* IRPC_ClientCheckResponse = nullptr; // 103
			IRPC* IRPC_GiveTakeDamage = nullptr; // 115
			IRPC* IRPC_GiveActorDamage = nullptr; // 177
			IRPC* IRPC_MapMarker = nullptr; // 119
			IRPC* IRPC_RequestClass = nullptr; // 128
			IRPC* IRPC_RequestSpawn = nullptr; // 129
			IRPC* IRPC_MenuQuit = nullptr; // 140
			IRPC* IRPC_MenuSelect = nullptr; // 132
			IRPC* IRPC_SelectTextDraw = nullptr; // 83
			IRPC* IRPC_PickedUpPickup = nullptr; // 131
			IRPC* IRPC_SelectObject = nullptr; // 27
			IRPC* IRPC_EditAttachedObject = nullptr; // 116
			IRPC* IRPC_EditObject = nullptr; // 117
			IRPC* IRPC_UpdateScoresAndPings = nullptr; // 155
			IRPC* IRPC_ClientJoin = nullptr; // 25
			IRPC* IRPC_NPCJoin = nullptr; // 54
			IRPC* IRPC_CameraTarget = nullptr; // 168
			IRPC* IRPC_Unsupported = nullptr; // -1
		}
	}
}



