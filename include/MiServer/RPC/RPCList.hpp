#ifndef __MISERVER_RCPLIST_HPP
#define __MISERVER_RCPLIST_HPP

#include <MiRak/NetworkTypes.h>
#include <MiServer/MiServer.hpp>

namespace mimp
{
	namespace internal
	{
		namespace RPC
		{
			namespace incoming
			{
				class Handler
				{
				public:
					static void EnterVehicle(RPCParameters *rpcParams);
					static void ExitVehicle(RPCParameters *rpcParams);
					static void VehicleDamaged(RPCParameters *rpcParams);
					static void ScmEvent(RPCParameters *rpcParams);
					static void VehicleDestroyed(RPCParameters *rpcParams);
					static void SendSpawn(RPCParameters *rpcParams);
					static void ChatMessage(RPCParameters *rpcParams);
					static void InteriorChangeNotification(RPCParameters *rpcParams);
					static void DeathNotification(RPCParameters *rpcParams);
					static void SendCommand(RPCParameters *rpcParams);
					static void ClickPlayer(RPCParameters *rpcParams);
					static void DialogResponse(RPCParameters *rpcParams);
					static void ClientCheckResponse(RPCParameters *rpcParams);
					static void GiveTakeDamage(RPCParameters *rpcParams);
					static void GiveActorDamage(RPCParameters *rpcParams);
					static void MapMarker(RPCParameters *rpcParams);
					static void RequestClass(RPCParameters *rpcParams);
					static void RequestSpawn(RPCParameters *rpcParams);
					static void MenuSelect(RPCParameters *rpcParams);
					static void MenuQuit(RPCParameters *rpcParams);
					static void SelectTextDraw(RPCParameters *rpcParams);
					static void PickedUpPickup(RPCParameters *rpcParams);
					static void SelectObject(RPCParameters *rpcParams);
					static void EditAttachedObject(RPCParameters *rpcParams);
					static void EditObject(RPCParameters *rpcParams);
					static void UpdateScoresAndPings(RPCParameters *rpcParams);
					static void ClientJoin(RPCParameters *rpcParams);
					static void NPCJoin(RPCParameters *rpcParams);
					static void CameraTarget(RPCParameters *rpcParams);
					static void HandleUnsupported(RPCParameters *rpcParams);
				};

				extern int RPC_EnterVehicle;			   // 26
				extern int RPC_ExitVehicle;				   // 154
				extern int RPC_VehicleDamaged;			   // 106
				extern int RPC_ScmEvent;				   // 96
				extern int RPC_VehicleDestroyed;		   // 136
				extern int RPC_SendSpawn;				   // 52
				extern int RPC_ChatMessage;				   // 101
				extern int RPC_InteriorChangeNotification; // 118
				extern int RPC_DeathNotification;		   // 53
				extern int RPC_SendCommand;				   // 50
				extern int RPC_ClickPlayer;				   // 23
				extern int RPC_DialogResponse;			   // 62
				extern int RPC_ClientCheckResponse;		   // 103
				extern int RPC_GiveTakeDamage;			   // 115
				extern int RPC_GiveActorDamage;			   // 177
				extern int RPC_MapMarker;				   // 119
				extern int RPC_RequestClass;			   // 128
				extern int RPC_RequestSpawn;			   // 129
				extern int RPC_MenuSelect;				   // 132
				extern int RPC_MenuQuit;				   // 140
				extern int RPC_SelectTextDraw;			   // 83
				extern int RPC_PickedUpPickup;			   // 131
				extern int RPC_SelectObject;			   // 27
				extern int RPC_EditAttachedObject;		   // 116
				extern int RPC_EditObject;				   // 117
				extern int RPC_UpdateScoresAndPings;	   // 155
				extern int RPC_ClientJoin;				   // 25
				extern int RPC_NPCJoin;					   // 54
				extern int RPC_CameraTarget;			   // 168

				void HandleUnsupported(RPCParameters *rpcParams);

			}

			namespace outgoing
			{
				class Handler
				{
				public:
					// Actor functions
					// static void ShowActor(void);
					// static void HideActor(void);
					// static void ApplyActorAnimation(void);
					// static void ClearActorAnimation(void);
					// static void SetActorFacingAngle(void);
					// static void SetActorPos(void);
					// static void SetActorHealth(void);

					// Player functions
					// static void SetPlayerAttachedObject(void);
					// static void ChatBubble(void);
					// static void DisableCheckpoint(void);
					// static void SetRaceCheckpoint(void);
					// static void DisableRaceCheckpoint(void);
					static void SetCheckpoint(const int playerid, const float x, const float y, const float z, const float sz);
					// static void ShowDialog(void);
					// static void AddGangZone(void);
					// static void GangZoneDestroy(void);
					// static void GangZoneFlash(void);
					// static void GangZoneStopFlash(void);
					// static void ShowGameText(void);
					// static void SetGravity(void);
					// static void SetMapIcon(void);
					// static void RemoveMapIcon(void);
					// static void ShowMenu(void);
					// static void HideMenu(void);
					// static void ShowPlayerNameTag(void);
					// static void CreateObject(void);
					// static void SetPlayerObjectMaterial(void);
					// static void AttachObjectToPlayer(void);
					// static void AttachCameraToObject(void);
					// static void EditAttachedObject(void);
					// static void EditObject(void);
					// static void EnterEditObject(void);
					// static void CancelEdit(void);
					// static void SetObjectPos(void);
					// static void SetObjectRotation(void);
					// static void DestroyObject(void);
					// static void MoveObject(void);
					// static void StopObject(void);
					// static void CreatePickup(void);
					// static void DestroyPickup(void);
					static void SetPlayerFacingAngle(const int playerid, const float a);
					static void ServerJoin(void);
					static void ServerQuit(void);
					static void InitGame(const int playerID, const bool zoneNames, const bool useCJWalk, const bool allowedWeapons, const bool limitGlobalChatRadius,
										 const float globalChatRadius, const bool stuntBonus, const float nameTagDrawDistance, const bool disableEnterExits,
										 const bool nameTagLOS, const bool manualVehicleEngineAndLight, const int spawnsAvailable,
										 const bool showPlayerTags, const int showPlayerMarkers, const BYTE worldTime, const BYTE weather,
										 const float gravity, const bool lanMode, const int deathDropMoney, const bool instagib, const int netModeNormalOnfootSendRate,
										 const int netModeNormalIncarSendRate, const int netModeFiringSendRate, const int netModeSendMultiplier,
										 const BYTE lagCompensation);
					static void UpdateScoresAndPings(void);

					// static void ClientCheck(void);
					// static void GameModeRestart(void);
					// static void ApplyPlayerAnimation(void);
					// static void ClearPlayerAnimation(void);
					// static void DeathBroadcast(void);
					// static void SetPlayerName(void);
					static void SetPlayerPos(const int playerid, const float x, const float y, const float z);
					// static void SetPlayerPosFindZ(void);
					// static void SetPlayerSkillLevel(void);
					static void SetPlayerSkin(const int playerid, const int skinid);
					// static void SetPlayerTime(void);
					// static void SetPlayerSpecialAction(void);
					// static void SetWeather(void);
					// static void SetWorldBounds(void);
					// static void SetPlayerVelocity(void);
					// static void TogglePlayerControllable(void);
					// static void TogglePlayerSpectating(void);
					// static void ToggleClock(void);
					// static void SetPlayerTeam(void);
					// static void PlaySound(void);
					// static void GivePlayerMoney(const int playerid, const int quant);
					// static void ResetPlayerMoney(const int playerid);
					// static void ResetPlayerWeapons(const int playerid);
					// static void GivePlayerWeapon(const int playerid, const int weaponid);
					// static void PlayAudioStream(void);
					// static void PlayCrimeReport(void);
					// static void StopAudioStream(void);
					// static void RemoveBuilding(void);
					static void SetPlayerHealth(const int playerid, const float value);
					static void SetPlayerArmour(const int playerid, const float value);
					// static void SetWeaponAmmo(const int playerid, const int quant);
					// static void SetCameraBehind(void);
					// static void SetArmedWeapon(void);
					static void WorldPlayerAdd(void);
					static void WorldPlayerRemove(void);
					// static void InterpolateCamera(void);
					// static void CreateExplosion(void);
					// static void SendDeathMessage(void);
					// static void SendGameTimeUpdate(void);
					static void SendClientMessage(const int playerid, const int color, const int messageLength, const char *message);
					// static void SetShopName(void);
					// static void SetPlayerDrunkLevel(void);
					// static void SetPlayerFightingStyle(const int playerid, const int style);
					// static void SetInterior(void);
					static void SetPlayerColor(const int playerid, const unsigned long color);
					// static void ForceClassSelection(void);
					// static void ToggleWidescreen(void);
					// static void SetPlayerWantedLevel(void);
					// static void SetCameraPos(void);
					// static void SetCameraLookAt(void);
					static void SetSpawnInfo(void);
					static void RequestClass(void);
					static void RequestSpawn(void);
					// static void SpectatePlayer(void);
					// static void SpectateVehicle(void);
					// static void EnableStuntBonus(void);
					// static void ToggleSelectTextDraw(void);
					// static void TextDrawSetString(void);
					// static void ShowTextDraw(void);
					// static void HideTextDraw(void);

					// Vehicle
					static void PlayerEnterVehicle(const WORD playerid, const WORD vehicleid, const BYTE passenger);
					static void PlayerExitVehicle(const WORD playerid, const WORD vehicleid);
					// static void RemoveVehicleComponent(void);
					// static void AttachTrailerToVehicle(void);
					// static void DetachTrailerFromVehicle(void);
					// static void LinkVehicleToInterior(void);
					// static void PutPlayerInVehicle(void);
					// static void RemovePlayerFromVehicle(void);
					// static void UpdateVehicleDamageStatus(void);
					// static void ScmEvent(void);
					// static void SetVehicleNumberPlate(void);
					// static void DisableVehicleCollisions(void);
					// static void SetVehicleHealth(void);
					// static void SetVehicleVelocity(void);
					// static void SetVehiclePos(void);
					// static void SetVehicleZAngle(void);
					// static void SetVehicleParams(void);
					// static void SetVehicleParamsEx(void);
					static void WorldVehicleAdd(CVehicle *veh, const int playerid);
					static void WorldVehicleRemove(const WORD idx, const int playerid);
					static void ConnectionRejected(void);
				};

				extern int RPC_ShowActor;				  // 171
				extern int RPC_HideActor;				  // 172
				extern int RPC_ApplyActorAnimation;		  // 173
				extern int RPC_ClearActorAnimation;		  // 174
				extern int RPC_SetActorFacingAngle;		  // 175
				extern int RPC_SetActorPos;				  // 176
				extern int RPC_SetActorHealth;			  // 178
				extern int RPC_SetPlayerAttachedObject;	  // 113
				extern int RPC_ChatBubble;				  // 59
				extern int RPC_DisableCheckpoint;		  // 37
				extern int RPC_SetRaceCheckpoint;		  // 38
				extern int RPC_DisableRaceCheckpoint;	  // 39
				extern int RPC_SetCheckpoint;			  // 107
				extern int RPC_ShowDialog;				  // 61
				extern int RPC_AddGangZone;				  // 108
				extern int RPC_GangZoneDestroy;			  // 120
				extern int RPC_GangZoneFlash;			  // 121
				extern int RPC_GangZoneStopFlash;		  // 85
				extern int RPC_ShowGameText;			  // 73
				extern int RPC_SetGravity;				  // 146
				extern int RPC_SetMapIcon;				  // 56
				extern int RPC_RemoveMapIcon;			  // 144
				extern int RPC_ShowMenu;				  // 77
				extern int RPC_HideMenu;				  // 78
				extern int RPC_ShowPlayerNameTag;		  // 80
				extern int RPC_CreateObject;			  // 44
				extern int RPC_SetPlayerObjectMaterial;	  // 84
				extern int RPC_AttachObjectToPlayer;	  // 75
				extern int RPC_AttachCameraToObject;	  // 81
				extern int RPC_EditAttachedObject;		  // 116
				extern int RPC_EditObject;				  // 117
				extern int RPC_EnterEditObject;			  // 27
				extern int RPC_CancelEdit;				  // 28
				extern int RPC_SetObjectPos;			  // 45
				extern int RPC_SetObjectRotation;		  // 46
				extern int RPC_DestroyObject;			  // 47
				extern int RPC_MoveObject;				  // 99
				extern int RPC_StopObject;				  // 122
				extern int RPC_CreatePickup;			  // 95
				extern int RPC_DestroyPickup;			  // 63
				extern int RPC_SetPlayerFacingAngle;	  // 19
				extern int RPC_ServerJoin;				  // 137
				extern int RPC_ServerQuit;				  // 138
				extern int RPC_InitGame;				  // 139
				extern int RPC_UpdateScoresAndPings;	  // 155
				extern int RPC_ClientCheck;				  // 103
				extern int RPC_GameModeRestart;			  // 40
				extern int RPC_ApplyPlayerAnimation;	  // 86
				extern int RPC_ClearPlayerAnimation;	  // 87
				extern int RPC_DeathBroadcast;			  // 166
				extern int RPC_SetPlayerName;			  // 11
				extern int RPC_SetPlayerPos;			  // 12
				extern int RPC_SetPlayerPosFindZ;		  // 13
				extern int RPC_SetPlayerSkillLevel;		  // 34
				extern int RPC_SetPlayerSkin;			  // 153
				extern int RPC_SetPlayerTime;			  // 29
				extern int RPC_SetPlayerSpecialAction;	  // 88
				extern int RPC_SetWeather;				  // 152
				extern int RPC_SetWorldBounds;			  // 17
				extern int RPC_SetPlayerVelocity;		  // 90
				extern int RPC_TogglePlayerControllable;  // 15
				extern int RPC_TogglePlayerSpectating;	  // 124
				extern int RPC_ToggleClock;				  // 30
				extern int RPC_SetPlayerTeam;			  // 69
				extern int RPC_PlaySound;				  // 16
				extern int RPC_GivePlayerMoney;			  // 18
				extern int RPC_ResetPlayerMoney;		  // 20
				extern int RPC_ResetPlayerWeapons;		  // 21
				extern int RPC_GivePlayerWeapon;		  // 22
				extern int RPC_PlayAudioStream;			  // 41
				extern int RPC_PlayCrimeReport;			  // 112
				extern int RPC_StopAudioStream;			  // 42
				extern int RPC_RemoveBuilding;			  // 43
				extern int RPC_SetPlayerHealth;			  // 14
				extern int RPC_SetPlayerArmour;			  // 66
				extern int RPC_SetWeaponAmmo;			  // 145
				extern int RPC_SetCameraBehind;			  // 162
				extern int RPC_SetArmedWeapon;			  // 67
				extern int RPC_WorldPlayerAdd;			  // 32
				extern int RPC_WorldPlayerRemove;		  // 163
				extern int RPC_InterpolateCamera;		  // 82
				extern int RPC_CreateExplosion;			  // 79
				extern int RPC_SendDeathMessage;		  // 55
				extern int RPC_SendGameTimeUpdate;		  // 60
				extern int RPC_SendClientMessage;		  // 93
				extern int RPC_SetShopName;				  // 33
				extern int RPC_SetPlayerDrunkLevel;		  // 35
				extern int RPC_SetPlayerFightingStyle;	  // 89
				extern int RPC_SetInterior;				  // 156
				extern int RPC_SetPlayerColor;			  // 72
				extern int RPC_ForceClassSelection;		  // 74
				extern int RPC_ToggleWidescreen;		  // 111
				extern int RPC_SetPlayerWantedLevel;	  // 133
				extern int RPC_SetCameraPos;			  // 157
				extern int RPC_SetCameraLookAt;			  // 158
				extern int RPC_SetSpawnInfo;			  // 68
				extern int RPC_RequestClass;			  // 128
				extern int RPC_RequestSpawn;			  // 129
				extern int RPC_SpectatePlayer;			  // 126
				extern int RPC_SpectateVehicle;			  // 127
				extern int RPC_EnableStuntBonus;		  // 104
				extern int RPC_ToggleSelectTextDraw;	  // 83
				extern int RPC_TextDrawSetString;		  // 105
				extern int RPC_ShowTextDraw;			  // 134
				extern int RPC_HideTextDraw;			  // 135
				extern int RPC_PlayerEnterVehicle;		  // 26
				extern int RPC_PlayerExitVehicle;		  // 154
				extern int RPC_RemoveVehicleComponent;	  // 57
				extern int RPC_AttachTrailerToVehicle;	  // 148
				extern int RPC_DetachTrailerFromVehicle;  // 149
				extern int RPC_LinkVehicleToInterior;	  // 65
				extern int RPC_PutPlayerInVehicle;		  // 70
				extern int RPC_RemovePlayerFromVehicle;	  // 71
				extern int RPC_UpdateVehicleDamageStatus; // 106
				extern int RPC_ScmEvent;				  // 96
				extern int RPC_SetVehicleNumberPlate;	  // 123
				extern int RPC_DisableVehicleCollisions;  // 167
				extern int RPC_SetVehicleHealth;		  // 147
				extern int RPC_SetVehicleVelocity;		  // 91
				extern int RPC_SetVehiclePos;			  // 159
				extern int RPC_SetVehicleZAngle;		  // 160
				extern int RPC_SetVehicleParams;		  // 161
				extern int RPC_SetVehicleParamsEx;		  // 24
				extern int RPC_WorldVehicleAdd;			  // 164
				extern int RPC_ConnectionRejected;		  // 130

			}
		}
	}
}
#endif