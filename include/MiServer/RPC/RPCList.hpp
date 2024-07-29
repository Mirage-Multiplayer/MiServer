#ifndef __MISERVER_RCPLIST_HPP
#define __MISERVER_RCPLIST_HPP
#include <MiRak/NetworkTypes.h>

namespace mimp {
	namespace internal {
		namespace RPC {
			namespace incomming {
				extern int RPC_EnterVehicle; // 26
				void EnterVehicle(RPCParameters* rpcParams);

				extern int RPC_ExitVehicle; // 154
				void ExitVehicle(RPCParameters* rpcParams);

				extern int RPC_VehicleDamaged; // 106
				void VehicleDamaged(RPCParameters* rpcParams);

				extern int RPC_ScmEvent; // 96
				void ScmEvent(RPCParameters* rpcParams);

				extern int RPC_VehicleDestroyed; // 136
				void VehicleDestroyed(RPCParameters* rpcParams);

				extern int RPC_SendSpawn; // 52
				void SendSpawn(RPCParameters* rpcParams);

				extern int RPC_ChatMessage; // 101
				void ChatMessage(RPCParameters* rpcParams);

				extern int RPC_InteriorChangeNotification; // 118
				void InteriorChangeNotification(RPCParameters* rpcParams);

				extern int RPC_DeathNotification; // 53
				void DeathNotification(RPCParameters* rpcParams);

				extern int RPC_SendCommand; // 50
				void SendCommand(RPCParameters* rpcParams);

				extern int RPC_ClickPlayer; // 23
				void ClickPlayer(RPCParameters* rpcParams);

				extern int RPC_DialogResponse; // 62
				void DialogResponse(RPCParameters* rpcParams);

				extern int RPC_ClientCheckResponse; // 103
				void ClientCheckResponse(RPCParameters* rpcParams);

				extern int RPC_GiveTakeDamage; // 115
				void GiveTakeDamage(RPCParameters* rpcParams);

				extern int RPC_GiveActorDamage; // 177
				void GiveActorDamage(RPCParameters* rpcParams);

				extern int RPC_MapMarker; // 119
				void MapMarker(RPCParameters* rpcParams);

				extern int RPC_RequestClass; // 128
				void RequestClass(RPCParameters* rpcParams);

				extern int RPC_RequestSpawn; // 129
				void RequestSpawn(RPCParameters* rpcParams);

				extern int RPC_MenuSelect; // 132
				void MenuSelect(RPCParameters* rpcParams);

				extern int RPC_MenuQuit; // 140
				void MenuQuit(RPCParameters* rpcParams);

				extern int RPC_SelectTextDraw; // 83
				void SelectTextDraw(RPCParameters* rpcParams);

				extern int RPC_PickedUpPickup; // 131
				void PickedUpPickup(RPCParameters* rpcParams);

				extern int RPC_SelectObject; // 27
				void SelectObject(RPCParameters* rpcParams);

				extern int RPC_EditAttachedObject; // 116
				void EditAttachedObject(RPCParameters* rpcParams);

				extern int RPC_EditObject; // 117
				void EditObject(RPCParameters* rpcParams);

				extern int RPC_UpdateScoresAndPings; // 155
				void UpdateScoresAndPings(RPCParameters* rpcParams);

				extern int RPC_ClientJoin; // 25
				void ClientJoin(RPCParameters* rpcParams);

				extern int RPC_NPCJoin; // 54
				void NPCJoin(RPCParameters* rpcParams);

				extern int RPC_CameraTarget; // 168
				void CameraTarget(RPCParameters* rpcParams);

				void HandleUnsupported(RPCParameters* rpcParams);

			}

			namespace outgoing {
				extern int RPC_ShowActor; // 171
				//void ShowActor(RPCParameters* rpcParams);

				extern int RPC_HideActor; // 172
				//void HideActor(RPCParameters* rpcParams);

				extern int RPC_ApplyActorAnimation; // 173
				//void ApplyActorAnimation(RPCParameters* rpcParams);

				extern int RPC_ClearActorAnimation; // 174
				//void ClearActorAnimation(RPCParameters* rpcParams);

				extern int RPC_SetActorFacingAngle; // 175
				//void SetActorFacingAngle(RPCParameters* rpcParams);

				extern int RPC_SetActorPos; // 176
				//void SetActorPos(RPCParameters* rpcParams);

				extern int RPC_SetActorHealth; // 178
				//void SetActorHealth(RPCParameters* rpcParams);

				extern int RPC_SetPlayerAttachedObject; // 113
				//void SetPlayerAttachedObject(RPCParameters* rpcParams);

				extern int RPC_ChatBubble; // 59
				//void ChatBubble(RPCParameters* rpcParams);

				extern int RPC_DisableCheckpoint; // 37
				//void DisableCheckpoint(RPCParameters* rpcParams);

				extern int RPC_SetRaceCheckpoint; // 38
				//void SetRaceCheckpoint(RPCParameters* rpcParams);

				extern int RPC_DisableRaceCheckpoint; // 39
				//void DisableRaceCheckpoint(RPCParameters* rpcParams);

				extern int RPC_SetCheckpoint; // 107
				//void SetCheckpoint(RPCParameters* rpcParams);

				extern int RPC_ShowDialog; // 61
				//void ShowDialog(RPCParameters* rpcParams);

				extern int RPC_AddGangZone; // 108
				//void AddGangZone(RPCParameters* rpcParams);

				extern int RPC_GangZoneDestroy; // 120
				//void GangZoneDestroy(RPCParameters* rpcParams);

				extern int RPC_GangZoneFlash; // 121
				//void GangZoneFlash(RPCParameters* rpcParams);

				extern int RPC_GangZoneStopFlash; // 85
				//void GangZoneStopFlash(RPCParameters* rpcParams);

				extern int RPC_ShowGameText; // 73
				//void ShowGameText(RPCParameters* rpcParams);

				extern int RPC_SetGravity; // 146
				//void SetGravity(RPCParameters* rpcParams);

				extern int RPC_SetMapIcon; // 56
				//void SetMapIcon(RPCParameters* rpcParams);

				extern int RPC_RemoveMapIcon; // 144
				//void RemoveMapIcon(RPCParameters* rpcParams);

				extern int RPC_ShowMenu; // 77
				//void ShowMenu(RPCParameters* rpcParams);

				extern int RPC_HideMenu; // 78
				//void HideMenu(RPCParameters* rpcParams);

				extern int RPC_ShowPlayerNameTag; // 80
				//void ShowPlayerNameTag(RPCParameters* rpcParams);

				extern int RPC_CreateObject; // 44
				//void CreateObject(RPCParameters* rpcParams);

				extern int RPC_SetPlayerObjectMaterial; // 84
				//void SetPlayerObjectMaterial(RPCParameters* rpcParams);

				extern int RPC_AttachObjectToPlayer; // 75
				//void AttachObjectToPlayer(RPCParameters* rpcParams);

				extern int RPC_AttachCameraToObject; // 81
				//void AttachCameraToObject(RPCParameters* rpcParams);

				extern int RPC_EditAttachedObject; // 116
				//void EditAttachedObject(RPCParameters* rpcParams);

				extern int RPC_EditObject; // 117
				//void EditObject(RPCParameters* rpcParams);

				extern int RPC_EnterEditObject; // 27
				//void EnterEditObject(RPCParameters* rpcParams);

				extern int RPC_CancelEdit; // 28
				//void CancelEdit(RPCParameters* rpcParams);

				extern int RPC_SetObjectPos; // 45
				//void SetObjectPos(RPCParameters* rpcParams);

				extern int RPC_SetObjectRotation; // 46
				//void SetObjectRotation(RPCParameters* rpcParams);

				extern int RPC_DestroyObject; // 47
				//void DestroyObject(RPCParameters* rpcParams);

				extern int RPC_MoveObject; // 99
				//void MoveObject(RPCParameters* rpcParams);

				extern int RPC_StopObject; // 122
				//void StopObject(RPCParameters* rpcParams);

				extern int RPC_CreatePickup; // 95
				//void CreatePickup(RPCParameters* rpcParams);

				extern int RPC_DestroyPickup; // 63
				//void DestroyPickup(RPCParameters* rpcParams);

				extern int RPC_SetPlayerFacingAngle; // 19
				//void SetPlayerFacingAngle(RPCParameters* rpcParams);

				extern int RPC_ServerJoin; // 137
				//void ServerJoin(RPCParameters* rpcParams);

				extern int RPC_ServerQuit; // 138
				//void ServerQuit(RPCParameters* rpcParams);

				extern int RPC_InitGame; // 139
				//void InitGame(RPCParameters* rpcParams);

				extern int RPC_UpdateScoresAndPings; // 155
				//void UpdateScoresAndPings(RPCParameters* rpcParams);

				extern int RPC_ClientCheck; // 103
				//void ClientCheck(RPCParameters* rpcParams);

				extern int RPC_GameModeRestart; // 40
				//void GameModeRestart(RPCParameters* rpcParams);

				extern int RPC_ApplyPlayerAnimation; // 86
				//void ApplyPlayerAnimation(RPCParameters* rpcParams);

				extern int RPC_ClearPlayerAnimation; // 87
				//void ClearPlayerAnimation(RPCParameters* rpcParams);

				extern int RPC_DeathBroadcast; // 166
				//void DeathBroadcast(RPCParameters* rpcParams);

				extern int RPC_SetPlayerName; // 11
				//void SetPlayerName(RPCParameters* rpcParams);

				extern int RPC_SetPlayerPos; // 12
				//void SetPlayerPos(RPCParameters* rpcParams);

				extern int RPC_SetPlayerPosFindZ; // 13
				//void SetPlayerPosFindZ(RPCParameters* rpcParams);

				extern int RPC_SetPlayerSkillLevel; // 34
				//void SetPlayerSkillLevel(RPCParameters* rpcParams);

				extern int RPC_SetPlayerSkin; // 153
				//void SetPlayerSkin(RPCParameters* rpcParams);

				extern int RPC_SetPlayerTime; // 29
				//void SetPlayerTime(RPCParameters* rpcParams);

				extern int RPC_SetPlayerSpecialAction; // 88
				//void SetPlayerSpecialAction(RPCParameters* rpcParams);

				extern int RPC_SetWeather; // 152
				//void SetWeather(RPCParameters* rpcParams);

				extern int RPC_SetWorldBounds; // 17
				//void SetWorldBounds(RPCParameters* rpcParams);

				extern int RPC_SetPlayerVelocity; // 90
				//void SetPlayerVelocity(RPCParameters* rpcParams);

				extern int RPC_TogglePlayerControllable; // 15
				//void TogglePlayerControllable(RPCParameters* rpcParams);

				extern int RPC_TogglePlayerSpectating; // 124
				//void TogglePlayerSpectating(RPCParameters* rpcParams);

				extern int RPC_ToggleClock; // 30
				//void ToggleClock(RPCParameters* rpcParams);

				extern int RPC_SetPlayerTeam; // 69
				//void SetPlayerTeam(RPCParameters* rpcParams);

				extern int RPC_PlaySound; // 16
				//void PlaySound(RPCParameters* rpcParams);

				extern int RPC_GivePlayerMoney; // 18
				//void GivePlayerMoney(RPCParameters* rpcParams);

				extern int RPC_ResetPlayerMoney; // 20
				//void ResetPlayerMoney(RPCParameters* rpcParams);

				extern int RPC_ResetPlayerWeapons; // 21
				//void ResetPlayerWeapons(RPCParameters* rpcParams);

				extern int RPC_GivePlayerWeapon; // 22
				//void GivePlayerWeapon(RPCParameters* rpcParams);

				extern int RPC_PlayAudioStream; // 41
				//void PlayAudioStream(RPCParameters* rpcParams);

				extern int RPC_PlayCrimeReport; // 112
				//void PlayCrimeReport(RPCParameters* rpcParams);

				extern int RPC_StopAudioStream; // 42
				//void StopAudioStream(RPCParameters* rpcParams);

				extern int RPC_RemoveBuilding; // 43
				//void RemoveBuilding(RPCParameters* rpcParams);

				extern int RPC_SetPlayerHealth; // 14
				//void SetPlayerHealth(RPCParameters* rpcParams);

				extern int RPC_SetPlayerArmour; // 66
				//void SetPlayerArmour(RPCParameters* rpcParams);

				extern int RPC_SetWeaponAmmo; // 145
				//void SetWeaponAmmo(RPCParameters* rpcParams);

				extern int RPC_SetCameraBehind; // 162
				//void SetCameraBehind(RPCParameters* rpcParams);

				extern int RPC_SetArmedWeapon; // 67
				//void SetArmedWeapon(RPCParameters* rpcParams);

				extern int RPC_WorldPlayerAdd; // 32
				//void WorldPlayerAdd(RPCParameters* rpcParams);

				extern int RPC_WorldPlayerRemove; // 163
				//void WorldPlayerRemove(RPCParameters* rpcParams);

				extern int RPC_InterpolateCamera; // 82
				//void InterpolateCamera(RPCParameters* rpcParams);

				extern int RPC_CreateExplosion; // 79
				//void CreateExplosion(RPCParameters* rpcParams);

				extern int RPC_SendDeathMessage; // 55
				//void SendDeathMessage(RPCParameters* rpcParams);

				extern int RPC_SendGameTimeUpdate; // 60
				//void SendGameTimeUpdate(RPCParameters* rpcParams);

				extern int RPC_SendClientMessage; // 93
				//void SendClientMessage(RPCParameters* rpcParams);

				extern int RPC_SetShopName; // 33
				//void SetShopName(RPCParameters* rpcParams);

				extern int RPC_SetPlayerDrunkLevel; // 35
				//void SetPlayerDrunkLevel(RPCParameters* rpcParams);

				extern int RPC_SetPlayerFightingStyle; // 89
				//void SetPlayerFightingStyle(RPCParameters* rpcParams);

				extern int RPC_SetInterior; // 156
				//void SetInterior(RPCParameters* rpcParams);

				extern int RPC_SetPlayerColor; // 72
				//void SetPlayerColor(RPCParameters* rpcParams);

				extern int RPC_ForceClassSelection; // 74
				//void ForceClassSelection(RPCParameters* rpcParams);

				extern int RPC_ToggleWidescreen; // 111
				//void ToggleWidescreen(RPCParameters* rpcParams);

				extern int RPC_SetPlayerWantedLevel; // 133
				//void SetPlayerWantedLevel(RPCParameters* rpcParams);

				extern int RPC_SetCameraPos; // 157
				//void SetCameraPos(RPCParameters* rpcParams);

				extern int RPC_SetCameraLookAt; // 158
				//void SetCameraLookAt(RPCParameters* rpcParams);

				extern int RPC_SetSpawnInfo; // 68
				//void SetSpawnInfo(RPCParameters* rpcParams);

				extern int RPC_RequestClass; // 128
				//void RequestClass(RPCParameters* rpcParams);

				extern int RPC_RequestSpawn; // 129
				//void RequestSpawn(RPCParameters* rpcParams);

				extern int RPC_SpectatePlayer; // 126
				//void SpectatePlayer(RPCParameters* rpcParams);

				extern int RPC_SpectateVehicle; // 127
				//void SpectateVehicle(RPCParameters* rpcParams);

				extern int RPC_EnableStuntBonus; // 104
				//void EnableStuntBonus(RPCParameters* rpcParams);

				extern int RPC_ToggleSelectTextDraw; // 83
				//void ToggleSelectTextDraw(RPCParameters* rpcParams);

				extern int RPC_TextDrawSetString; // 105
				//void TextDrawSetString(RPCParameters* rpcParams);

				extern int RPC_ShowTextDraw; // 134
				//void ShowTextDraw(RPCParameters* rpcParams);

				extern int RPC_HideTextDraw; // 135
				//void HideTextDraw(RPCParameters* rpcParams);

				extern int RPC_PlayerEnterVehicle; // 26
				//void PlayerEnterVehicle(RPCParameters* rpcParams);

				extern int RPC_PlayerExitVehicle; // 154
				//void PlayerExitVehicle(RPCParameters* rpcParams);

				extern int RPC_RemoveVehicleComponent; // 57
				//void RemoveVehicleComponent(RPCParameters* rpcParams);

				extern int RPC_AttachTrailerToVehicle; // 148
				//void AttachTrailerToVehicle(RPCParameters* rpcParams);

				extern int RPC_DetachTrailerFromVehicle; // 149
				//void DetachTrailerFromVehicle(RPCParameters* rpcParams);

				extern int RPC_LinkVehicleToInterior; // 65
				//void LinkVehicleToInterior(RPCParameters* rpcParams);

				extern int RPC_PutPlayerInVehicle; // 70
				//void PutPlayerInVehicle(RPCParameters* rpcParams);

				extern int RPC_RemovePlayerFromVehicle; // 71
				//void RemovePlayerFromVehicle(RPCParameters* rpcParams);

				extern int RPC_UpdateVehicleDamageStatus; // 106
				//void UpdateVehicleDamageStatus(RPCParameters* rpcParams);

				extern int RPC_ScmEvent; // 96
				//void ScmEvent(RPCParameters* rpcParams);

				extern int RPC_SetVehicleNumberPlate; // 123
				//void SetVehicleNumberPlate(RPCParameters* rpcParams);

				extern int RPC_DisableVehicleCollisions; // 167
				//void DisableVehicleCollisions(RPCParameters* rpcParams);

				extern int RPC_SetVehicleHealth; // 147
				//void SetVehicleHealth(RPCParameters* rpcParams);

				extern int RPC_SetVehicleVelocity; // 91
				//void SetVehicleVelocity(RPCParameters* rpcParams);

				extern int RPC_SetVehiclePos; // 159
				//void SetVehiclePos(RPCParameters* rpcParams);

				extern int RPC_SetVehicleZAngle; // 160
				//void SetVehicleZAngle(RPCParameters* rpcParams);

				extern int RPC_SetVehicleParams; // 161
				//void SetVehicleParams(RPCParameters* rpcParams);

				extern int RPC_SetVehicleParamsEx; // 24
				//void SetVehicleParamsEx(RPCParameters* rpcParams);

				extern int RPC_WorldVehicleAdd; // 164

				extern int RPC_ConnectionRejected; // 130

			}  
		}
	}
}

#endif