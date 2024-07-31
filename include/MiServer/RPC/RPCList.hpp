#ifndef __MISERVER_RCPLIST_HPP
#define __MISERVER_RCPLIST_HPP
#include <MiRak/NetworkTypes.h>

namespace mimp {
	namespace internal {
		namespace RPC {
			namespace incomming {
				class Handler {
				public:
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
				};

				extern int RPC_EnterVehicle; // 26
				extern int RPC_ExitVehicle; // 154
				extern int RPC_VehicleDamaged; // 106
				extern int RPC_ScmEvent; // 96
				extern int RPC_VehicleDestroyed; // 136
				extern int RPC_SendSpawn; // 52
				extern int RPC_ChatMessage; // 101
				extern int RPC_InteriorChangeNotification; // 118
				extern int RPC_DeathNotification; // 53
				extern int RPC_SendCommand; // 50
				extern int RPC_ClickPlayer; // 23
				extern int RPC_DialogResponse; // 62
				extern int RPC_ClientCheckResponse; // 103
				extern int RPC_GiveTakeDamage; // 115
				extern int RPC_GiveActorDamage; // 177
				extern int RPC_MapMarker; // 119
				extern int RPC_RequestClass; // 128
				extern int RPC_RequestSpawn; // 129
				extern int RPC_MenuSelect; // 132
				extern int RPC_MenuQuit; // 140
				extern int RPC_SelectTextDraw; // 83
				extern int RPC_PickedUpPickup; // 131
				extern int RPC_SelectObject; // 27
				extern int RPC_EditAttachedObject; // 116
				extern int RPC_EditObject; // 117
				extern int RPC_UpdateScoresAndPings; // 155
				extern int RPC_ClientJoin; // 25
				extern int RPC_NPCJoin; // 54
				extern int RPC_CameraTarget; // 168

				void HandleUnsupported(RPCParameters* rpcParams);

			}

			namespace outgoing {
				class Handler {
				public:
					// Actor functions
					static void ShowActor(RPCParameters* rpcParams);
					static void HideActor(RPCParameters* rpcParams);
					static void ApplyActorAnimation(RPCParameters* rpcParams);
					static void ClearActorAnimation(RPCParameters* rpcParams);
					static void SetActorFacingAngle(RPCParameters* rpcParams);
					static void SetActorPos(RPCParameters* rpcParams);
					static void SetActorHealth(RPCParameters* rpcParams);

					// Player functions
					static void SetPlayerAttachedObject(RPCParameters* rpcParams);
					static void ChatBubble(RPCParameters* rpcParams);
					static void DisableCheckpoint(RPCParameters* rpcParams);
					static void SetRaceCheckpoint(RPCParameters* rpcParams);
					static void DisableRaceCheckpoint(RPCParameters* rpcParams);
					static void SetCheckpoint(RPCParameters* rpcParams);
					static void ShowDialog(RPCParameters* rpcParams);
					static void AddGangZone(RPCParameters* rpcParams);
					static void GangZoneDestroy(RPCParameters* rpcParams);
					static void GangZoneFlash(RPCParameters* rpcParams);
					static void GangZoneStopFlash(RPCParameters* rpcParams);
					static void ShowGameText(RPCParameters* rpcParams);
					static void SetGravity(RPCParameters* rpcParams);
					static void SetMapIcon(RPCParameters* rpcParams);
					static void RemoveMapIcon(RPCParameters* rpcParams);
					static void ShowMenu(RPCParameters* rpcParams);
					static void HideMenu(RPCParameters* rpcParams);
					static void ShowPlayerNameTag(RPCParameters* rpcParams);
					static void CreateObject(RPCParameters* rpcParams);
					static void SetPlayerObjectMaterial(RPCParameters* rpcParams);
					static void AttachObjectToPlayer(RPCParameters* rpcParams);
					static void AttachCameraToObject(RPCParameters* rpcParams);
					static void EditAttachedObject(RPCParameters* rpcParams);
					static void EditObject(RPCParameters* rpcParams);
					static void EnterEditObject(RPCParameters* rpcParams);
					static void CancelEdit(RPCParameters* rpcParams);
					static void SetObjectPos(RPCParameters* rpcParams);
					static void SetObjectRotation(RPCParameters* rpcParams);
					static void DestroyObject(RPCParameters* rpcParams);
					static void MoveObject(RPCParameters* rpcParams);
					static void StopObject(RPCParameters* rpcParams);
					static void CreatePickup(RPCParameters* rpcParams);
					static void DestroyPickup(RPCParameters* rpcParams);
					static void SetPlayerFacingAngle(RPCParameters* rpcParams);
					static void ServerJoin(RPCParameters* rpcParams);
					static void ServerQuit(RPCParameters* rpcParams);
					static void InitGame(RPCParameters* rpcParams);
					static void UpdateScoresAndPings(RPCParameters* rpcParams);
					static void ClientCheck(RPCParameters* rpcParams);
					static void GameModeRestart(RPCParameters* rpcParams);
					static void ApplyPlayerAnimation(RPCParameters* rpcParams);
					static void ClearPlayerAnimation(RPCParameters* rpcParams);
					static void DeathBroadcast(RPCParameters* rpcParams);
					static void SetPlayerName(RPCParameters* rpcParams);
					static void SetPlayerPos(RPCParameters* rpcParams);
					static void SetPlayerPosFindZ(RPCParameters* rpcParams);
					static void SetPlayerSkillLevel(RPCParameters* rpcParams);
					static void SetPlayerSkin(RPCParameters* rpcParams);
					static void SetPlayerTime(RPCParameters* rpcParams);
					static void SetPlayerSpecialAction(RPCParameters* rpcParams);
					static void SetWeather(RPCParameters* rpcParams);
					static void SetWorldBounds(RPCParameters* rpcParams);
					static void SetPlayerVelocity(RPCParameters* rpcParams);
					static void TogglePlayerControllable(RPCParameters* rpcParams);
					static void TogglePlayerSpectating(RPCParameters* rpcParams);
					static void ToggleClock(RPCParameters* rpcParams);
					static void SetPlayerTeam(RPCParameters* rpcParams);
					//static void PlaySound(RPCParameters* rpcParams);
					static void GivePlayerMoney(RPCParameters* rpcParams);
					static void ResetPlayerMoney(RPCParameters* rpcParams);
					static void ResetPlayerWeapons(RPCParameters* rpcParams);
					static void GivePlayerWeapon(RPCParameters* rpcParams);
					static void PlayAudioStream(RPCParameters* rpcParams);
					static void PlayCrimeReport(RPCParameters* rpcParams);
					static void StopAudioStream(RPCParameters* rpcParams);
					static void RemoveBuilding(RPCParameters* rpcParams);
					static void SetPlayerHealth(RPCParameters* rpcParams);
					static void SetPlayerArmour(RPCParameters* rpcParams);
					static void SetWeaponAmmo(RPCParameters* rpcParams);
					static void SetCameraBehind(RPCParameters* rpcParams);
					static void SetArmedWeapon(RPCParameters* rpcParams);
					static void WorldPlayerAdd(RPCParameters* rpcParams);
					static void WorldPlayerRemove(RPCParameters* rpcParams);
					static void InterpolateCamera(RPCParameters* rpcParams);
					static void CreateExplosion(RPCParameters* rpcParams);
					static void SendDeathMessage(RPCParameters* rpcParams);
					static void SendGameTimeUpdate(RPCParameters* rpcParams);
					static void SendClientMessage(RPCParameters* rpcParams);
					static void SetShopName(RPCParameters* rpcParams);
					static void SetPlayerDrunkLevel(RPCParameters* rpcParams);
					static void SetPlayerFightingStyle(RPCParameters* rpcParams);
					static void SetInterior(RPCParameters* rpcParams);
					static void SetPlayerColor(RPCParameters* rpcParams);
					static void ForceClassSelection(RPCParameters* rpcParams);
					static void ToggleWidescreen(RPCParameters* rpcParams);
					static void SetPlayerWantedLevel(RPCParameters* rpcParams);
					static void SetCameraPos(RPCParameters* rpcParams);
					static void SetCameraLookAt(RPCParameters* rpcParams);
					static void SetSpawnInfo(RPCParameters* rpcParams);
					static void RequestClass(RPCParameters* rpcParams);
					static void RequestSpawn(RPCParameters* rpcParams);
					static void SpectatePlayer(RPCParameters* rpcParams);
					static void SpectateVehicle(RPCParameters* rpcParams);
					static void EnableStuntBonus(RPCParameters* rpcParams);
					static void ToggleSelectTextDraw(RPCParameters* rpcParams);
					static void TextDrawSetString(RPCParameters* rpcParams);
					static void ShowTextDraw(RPCParameters* rpcParams);
					static void HideTextDraw(RPCParameters* rpcParams);
					static void PlayerEnterVehicle(RPCParameters* rpcParams);
					static void PlayerExitVehicle(RPCParameters* rpcParams);
					static void RemoveVehicleComponent(RPCParameters* rpcParams);
					static void AttachTrailerToVehicle(RPCParameters* rpcParams);
					static void DetachTrailerFromVehicle(RPCParameters* rpcParams);
					static void LinkVehicleToInterior(RPCParameters* rpcParams);
					static void PutPlayerInVehicle(RPCParameters* rpcParams);
					static void RemovePlayerFromVehicle(RPCParameters* rpcParams);
					static void UpdateVehicleDamageStatus(RPCParameters* rpcParams);
					static void ScmEvent(RPCParameters* rpcParams);
					static void SetVehicleNumberPlate(RPCParameters* rpcParams);
					static void DisableVehicleCollisions(RPCParameters* rpcParams);
					static void SetVehicleHealth(RPCParameters* rpcParams);
					static void SetVehicleVelocity(RPCParameters* rpcParams);
					static void SetVehiclePos(RPCParameters* rpcParams);
					static void SetVehicleZAngle(RPCParameters* rpcParams);
					static void SetVehicleParams(RPCParameters* rpcParams);
					static void SetVehicleParamsEx(RPCParameters* rpcParams);
					static void WorldVehicleAdd(RPCParameters* rpcParams);
					static void ConnectionRejected(RPCParameters* rpcParams);
				};

				extern int RPC_ShowActor; // 171
				extern int RPC_HideActor; // 172
				extern int RPC_ApplyActorAnimation; // 173
				extern int RPC_ClearActorAnimation; // 174
				extern int RPC_SetActorFacingAngle; // 175
				extern int RPC_SetActorPos; // 176
				extern int RPC_SetActorHealth; // 178
				extern int RPC_SetPlayerAttachedObject; // 113
				extern int RPC_ChatBubble; // 59
				extern int RPC_DisableCheckpoint; // 37
				extern int RPC_SetRaceCheckpoint; // 38
				extern int RPC_DisableRaceCheckpoint; // 39
				extern int RPC_SetCheckpoint; // 107
				extern int RPC_ShowDialog; // 61
				extern int RPC_AddGangZone; // 108
				extern int RPC_GangZoneDestroy; // 120
				extern int RPC_GangZoneFlash; // 121
				extern int RPC_GangZoneStopFlash; // 85
				extern int RPC_ShowGameText; // 73
				extern int RPC_SetGravity; // 146
				extern int RPC_SetMapIcon; // 56
				extern int RPC_RemoveMapIcon; // 144
				extern int RPC_ShowMenu; // 77
				extern int RPC_HideMenu; // 78
				extern int RPC_ShowPlayerNameTag; // 80
				extern int RPC_CreateObject; // 44
				extern int RPC_SetPlayerObjectMaterial; // 84
				extern int RPC_AttachObjectToPlayer; // 75
				extern int RPC_AttachCameraToObject; // 81
				extern int RPC_EditAttachedObject; // 116
				extern int RPC_EditObject; // 117
				extern int RPC_EnterEditObject; // 27
				extern int RPC_CancelEdit; // 28
				extern int RPC_SetObjectPos; // 45
				extern int RPC_SetObjectRotation; // 46
				extern int RPC_DestroyObject; // 47
				extern int RPC_MoveObject; // 99
				extern int RPC_StopObject; // 122
				extern int RPC_CreatePickup; // 95
				extern int RPC_DestroyPickup; // 63
				extern int RPC_SetPlayerFacingAngle; // 19
				extern int RPC_ServerJoin; // 137
				extern int RPC_ServerQuit; // 138
				extern int RPC_InitGame; // 139
				extern int RPC_UpdateScoresAndPings; // 155
				extern int RPC_ClientCheck; // 103
				extern int RPC_GameModeRestart; // 40
				extern int RPC_ApplyPlayerAnimation; // 86
				extern int RPC_ClearPlayerAnimation; // 87
				extern int RPC_DeathBroadcast; // 166
				extern int RPC_SetPlayerName; // 11
				extern int RPC_SetPlayerPos; // 12
				extern int RPC_SetPlayerPosFindZ; // 13
				extern int RPC_SetPlayerSkillLevel; // 34
				extern int RPC_SetPlayerSkin; // 153
				extern int RPC_SetPlayerTime; // 29
				extern int RPC_SetPlayerSpecialAction; // 88
				extern int RPC_SetWeather; // 152
				extern int RPC_SetWorldBounds; // 17
				extern int RPC_SetPlayerVelocity; // 90
				extern int RPC_TogglePlayerControllable; // 15
				extern int RPC_TogglePlayerSpectating; // 124
				extern int RPC_ToggleClock; // 30
				extern int RPC_SetPlayerTeam; // 69
				extern int RPC_PlaySound; // 16
				extern int RPC_GivePlayerMoney; // 18
				extern int RPC_ResetPlayerMoney; // 20
				extern int RPC_ResetPlayerWeapons; // 21
				extern int RPC_GivePlayerWeapon; // 22
				extern int RPC_PlayAudioStream; // 41
				extern int RPC_PlayCrimeReport; // 112
				extern int RPC_StopAudioStream; // 42
				extern int RPC_RemoveBuilding; // 43
				extern int RPC_SetPlayerHealth; // 14
				extern int RPC_SetPlayerArmour; // 66
				extern int RPC_SetWeaponAmmo; // 145
				extern int RPC_SetCameraBehind; // 162
				extern int RPC_SetArmedWeapon; // 67
				extern int RPC_WorldPlayerAdd; // 32
				extern int RPC_WorldPlayerRemove; // 163
				extern int RPC_InterpolateCamera; // 82
				extern int RPC_CreateExplosion; // 79
				extern int RPC_SendDeathMessage; // 55
				extern int RPC_SendGameTimeUpdate; // 60
				extern int RPC_SendClientMessage; // 93
				extern int RPC_SetShopName; // 33
				extern int RPC_SetPlayerDrunkLevel; // 35
				extern int RPC_SetPlayerFightingStyle; // 89
				extern int RPC_SetInterior; // 156
				extern int RPC_SetPlayerColor; // 72
				extern int RPC_ForceClassSelection; // 74
				extern int RPC_ToggleWidescreen; // 111
				extern int RPC_SetPlayerWantedLevel; // 133
				extern int RPC_SetCameraPos; // 157
				extern int RPC_SetCameraLookAt; // 158
				extern int RPC_SetSpawnInfo; // 68
				extern int RPC_RequestClass; // 128
				extern int RPC_RequestSpawn; // 129
				extern int RPC_SpectatePlayer; // 126
				extern int RPC_SpectateVehicle; // 127
				extern int RPC_EnableStuntBonus; // 104
				extern int RPC_ToggleSelectTextDraw; // 83
				extern int RPC_TextDrawSetString; // 105
				extern int RPC_ShowTextDraw; // 134
				extern int RPC_HideTextDraw; // 135
				extern int RPC_PlayerEnterVehicle; // 26
				extern int RPC_PlayerExitVehicle; // 154
				extern int RPC_RemoveVehicleComponent; // 57
				extern int RPC_AttachTrailerToVehicle; // 148
				extern int RPC_DetachTrailerFromVehicle; // 149
				extern int RPC_LinkVehicleToInterior; // 65
				extern int RPC_PutPlayerInVehicle; // 70
				extern int RPC_RemovePlayerFromVehicle; // 71
				extern int RPC_UpdateVehicleDamageStatus; // 106
				extern int RPC_ScmEvent; // 96
				extern int RPC_SetVehicleNumberPlate; // 123
				extern int RPC_DisableVehicleCollisions; // 167
				extern int RPC_SetVehicleHealth; // 147
				extern int RPC_SetVehicleVelocity; // 91
				extern int RPC_SetVehiclePos; // 159
				extern int RPC_SetVehicleZAngle; // 160
				extern int RPC_SetVehicleParams; // 161
				extern int RPC_SetVehicleParamsEx; // 24
				extern int RPC_WorldVehicleAdd; // 164
				extern int RPC_ConnectionRejected; // 130

			}  
		}
	}
}

#endif