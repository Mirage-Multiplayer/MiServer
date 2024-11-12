#ifndef __MISERVER_RCPLIST_HPP
#define __MISERVER_RCPLIST_HPP

#include <MiRak/NetworkTypes.h>
#include <MiServerxx/MiServerxx.hpp>
#include <MiServerxx/RPC/RPC.hpp>

namespace mimp
{
	namespace internal
	{
		namespace RPC
		{
			/*
			IRPC<26> IRPC_EnterVehicle;
			IRPC<154> IRPC_ExitVehicle;
			IRPC<106> IRPC_VehicleDamaged;
			IRPC<96> IRPC_ScmEvent;
			IRPC<136> IRPC_VehicleDestroyed;
			IRPC<52> IRPC_SendSpawn;
			IRPC<101> IRPC_ChatMessage;
			IRPC<118> IRPC_InteriorChangeNotification;
			IRPC<53> IRPC_DeathNotification;
			IRPC<50> IRPC_SendCommand;
			IRPC<23> IRPC_ClickPlayer;
			IRPC<62> IRPC_DialogResponse;
			IRPC<103> IRPC_ClientCheckResponse;
			IRPC<115> IRPC_GiveTakeDamage;
			IRPC<177> IRPC_GiveActorDamage;
			IRPC<119> IRPC_MapMarker;
			IRPC<128> IRPC_RequestClass;
			IRPC<129> IRPC_RequestSpawn;
			IRPC<140> IRPC_MenuQuit;
			IRPC<132> IRPC_MenuSelect;
			IRPC<83> IRPC_SelectTextDraw;
			IRPC<131> IRPC_PickedUpPickup;
			IRPC<27> IRPC_SelectObject;
			IRPC<116> IRPC_EditAttachedObject;
			IRPC<117> IRPC_EditObject;
			IRPC<155> IRPC_UpdateScoresAndPings;
			IRPC<25> IRPC_ClientJoin;
			IRPC<54> IRPC_NPCJoin;
			IRPC<168> IRPC_CameraTarget;
			IRPC<-1> IRPC_Unsupported;
			*/
			
			extern IRPC* IRPC_EnterVehicle; // 26
			extern IRPC* IRPC_ExitVehicle;	// 154
			extern IRPC* IRPC_VehicleDamaged; // 106
			extern IRPC* IRPC_ScmEvent; // 96
			extern IRPC* IRPC_VehicleDestroyed; // 136
			extern IRPC* IRPC_SendSpawn; // 52
			extern IRPC* IRPC_ChatMessage; // 101
			extern IRPC* IRPC_InteriorChangeNotification; // 118
			extern IRPC* IRPC_DeathNotification; // 53
			extern IRPC* IRPC_SendCommand; // 50
			extern IRPC* IRPC_ClickPlayer; // 23
			extern IRPC* IRPC_DialogResponse; // 62
			extern IRPC* IRPC_ClientCheckResponse; // 103
			extern IRPC* IRPC_GiveTakeDamage; // 115
			extern IRPC* IRPC_GiveActorDamage; // 177
			extern IRPC* IRPC_MapMarker; // 119
			extern IRPC* IRPC_RequestClass; // 128
			extern IRPC* IRPC_RequestSpawn; // 129
			extern IRPC* IRPC_MenuQuit; // 140
			extern IRPC* IRPC_MenuSelect; // 132
			extern IRPC* IRPC_SelectTextDraw; // 83
			extern IRPC* IRPC_PickedUpPickup; // 131
			extern IRPC* IRPC_SelectObject; // 27
			extern IRPC* IRPC_EditAttachedObject; // 116
			extern IRPC* IRPC_EditObject; // 117
			extern IRPC* IRPC_UpdateScoresAndPings; // 155
			extern IRPC* IRPC_ClientJoin; // 25
			extern IRPC* IRPC_NPCJoin; // 54
			extern IRPC* IRPC_CameraTarget; // 168
			extern IRPC* IRPC_Unsupported; // -1


			// ShowActor - ID: 171
			struct ORPCShowActor : public ORPC {
				uint16_t wActorID;
				uint32_t SkinID;
				float X, Y, Z, Angle, Health;
				uint8_t Invulnerable;

				explicit ORPCShowActor() : ORPC(171) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wActorID);
					bs->Write(SkinID);
					bs->Write(X);
					bs->Write(Y);
					bs->Write(Z);
					bs->Write(Angle);
					bs->Write(Health);
					bs->Write(Invulnerable);
				}
			};

			// HideActor - ID: 172
			struct ORPCHideActor : public ORPC {
				uint16_t wActorID;

				explicit ORPCHideActor() : ORPC(172) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wActorID);
				}
			};

			// ApplyActorAnimation - ID: 173
			struct ORPCApplyActorAnimation : public ORPC {
				uint16_t wActorID;
				uint8_t AnimLibLength;
				char* AnimLib;
				uint8_t AnimNameLength;
				char* AnimName;
				float fDelta;
				bool loop, lockx, locky, freeze;
				uint32_t time;

				explicit ORPCApplyActorAnimation() : ORPC(173) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wActorID);
					bs->Write(AnimLibLength);
					bs->Write(AnimLib, AnimLibLength);
					bs->Write(AnimNameLength);
					bs->Write(AnimName, AnimNameLength);
					bs->Write(fDelta);
					bs->Write(loop);
					bs->Write(lockx);
					bs->Write(locky);
					bs->Write(freeze);
					bs->Write(time);
				}
			};

			// ClearActorAnimation - ID: 174
			struct ORPCClearActorAnimation : public ORPC {
				uint16_t wActorID;

				explicit ORPCClearActorAnimation() : ORPC(174) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wActorID);
				}
			};

			// SetActorFacingAngle - ID: 175
			struct ORPCSetActorFacingAngle : public ORPC {
				uint16_t wActorID;
				float angle;

				explicit ORPCSetActorFacingAngle() : ORPC(175) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wActorID);
					bs->Write(angle);
				}
			};

			// SetActorPos - ID: 176
			struct ORPCSetActorPos : public ORPC {
				uint16_t wActorID;
				float x, y, z;

				explicit ORPCSetActorPos() : ORPC(176) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wActorID);
					bs->Write(x);
					bs->Write(y);
					bs->Write(z);
				}
			};

			// SetActorHealth - ID: 178
			struct ORPCSetActorHealth : public ORPC {
				uint16_t wActorID;
				float health;

				explicit ORPCSetActorHealth() : ORPC(178) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wActorID);
					bs->Write(health);
				}
			};

			// SetPlayerAttachedObject - ID: 113
			struct ORPCSetPlayerAttachedObject : public ORPC {
				uint16_t playerid;
				uint32_t index, model, bone;
				bool create;
				float offsetX, offsetY, offsetZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ;
				uint32_t materialColor1, materialColor2;

				explicit ORPCSetPlayerAttachedObject() : ORPC(113) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(playerid);
					bs->Write(index);
					bs->Write(create);
					bs->Write(model);
					bs->Write(bone);
					bs->Write(offsetX);
					bs->Write(offsetY);
					bs->Write(offsetZ);
					bs->Write(rotX);
					bs->Write(rotY);
					bs->Write(rotZ);
					bs->Write(scaleX);
					bs->Write(scaleY);
					bs->Write(scaleZ);
					bs->Write(materialColor1);
					bs->Write(materialColor2);
				}
			};

			// ShowDialog - ID: 61
			struct ORPCShowDialog : public ORPC {
				int16_t wDialogID;
				uint8_t dialogStyle, titleLen, button1Len, button2Len;
				char* title;
				char* button1;
				char* button2;
				char info[4096];

				explicit ORPCShowDialog() : ORPC(61) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wDialogID);
					bs->Write(dialogStyle);
					bs->Write(titleLen);
					bs->Write(title, titleLen);
					bs->Write(button1Len);
					bs->Write(button1, button1Len);
					bs->Write(button2Len);
					bs->Write(button2, button2Len);
					bs->Write(info, sizeof(info));
				}
			};

			struct ORPCServerJoin : public ORPC {
				UINT16 wPlayerID;
				UINT32 dColor;
				UINT8 isNPC;
				UINT8 PlayerNameLength;
				char PlayerName[256];  // Assumindo que o nome do jogador não ultrapasse 255 caracteres

				explicit ORPCServerJoin() : ORPC(137) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wPlayerID);
					bs->Write(dColor);
					bs->Write(isNPC);
					bs->Write(PlayerNameLength);
					bs->Write(PlayerName, PlayerNameLength);
				}
			};

			struct ORPCServerQuit : public ORPC {
				UINT16 wPlayerID;
				UINT8 reason;

				explicit ORPCServerQuit() : ORPC(138) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wPlayerID);
					bs->Write(reason);
				}
			};

			struct ORPCInitGame : public ORPC {
				bool bZoneNames;
				bool bUseCJWalk;
				bool bAllowWeapons;
				bool bLimitGlobalChatRadius;
				float fGlobalChatRadius;
				bool bStuntBonus;
				float fNameTagDistance;
				bool bDisableEnterExits;
				bool bNameTagLOS;
				bool bManualVehEngineAndLights;
				UINT32 dSpawnsAvailable;
				UINT16 wPlayerID;
				bool bShowNameTags;
				UINT32 dShowPlayerMarkers;
				UINT8 bWorldTime;
				UINT8 bWeather;
				float fGravity;
				bool bLanMode;
				UINT32 dDeathDropMoney;
				bool bInstagib;
				UINT32 dOnfootRate;
				UINT32 dInCarRate;
				UINT32 dWeaponRate;
				UINT32 dMultiplier;
				UINT32 dLagCompMode;
				UINT8 length;
				char HostName[256];  // Assumindo que o nome do host não ultrapasse 255 caracteres
				UINT8 bVehicleModels[212];
				UINT32 dVehicleFriendlyFire;

				explicit ORPCInitGame() : ORPC(139) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(bZoneNames);
					bs->Write(bUseCJWalk);
					bs->Write(bAllowWeapons);
					bs->Write(bLimitGlobalChatRadius);
					bs->Write(fGlobalChatRadius);
					bs->Write(bStuntBonus);
					bs->Write(fNameTagDistance);
					bs->Write(bDisableEnterExits);
					bs->Write(bNameTagLOS);
					bs->Write(bManualVehEngineAndLights);
					bs->Write(dSpawnsAvailable);
					bs->Write(wPlayerID);
					bs->Write(bShowNameTags);
					bs->Write(dShowPlayerMarkers);
					bs->Write(bWorldTime);
					bs->Write(bWeather);
					bs->Write(fGravity);
					bs->Write(bLanMode);
					bs->Write(dDeathDropMoney);
					bs->Write(bInstagib);
					bs->Write(dOnfootRate);
					bs->Write(dInCarRate);
					bs->Write(dWeaponRate);
					bs->Write(dMultiplier);
					bs->Write(dLagCompMode);
					bs->Write(length);
					bs->Write(HostName, length);
					bs->Write((char*)bVehicleModels, sizeof(bVehicleModels));
					bs->Write(dVehicleFriendlyFire);
				}
			};

			struct ORPCConnectionRejected : public ORPC {
				UINT8 reason;

				explicit ORPCConnectionRejected() : ORPC(130) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(reason);
				}
			};

			struct ORPCUpdateScoresAndPings : public ORPC {
				UINT16 wPlayerID;
				INT32 score;
				UINT32 ping;

				explicit ORPCUpdateScoresAndPings() : ORPC(155) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wPlayerID);
					bs->Write(score);
					bs->Write(ping);
				}
			};

			struct ORPCGameModeRestart : public ORPC {
				explicit ORPCGameModeRestart() : ORPC(40) {}

				void Write(RakNet::BitStream* bs) override {
					// Não há parâmetros, apenas envia a RPC
				}
			};

			struct ORPCApplyPlayerAnimation : public ORPC {
				UINT16 wPlayerID;
				UINT8 AnimLibLength;
				char AnimLib[256];  // Assumindo que a animação não ultrapasse 255 caracteres
				UINT8 AnimNameLength;
				char AnimName[256]; // Assumindo que o nome da animação não ultrapasse 255 caracteres
				float fDelta;
				bool loop;
				bool lockx;
				bool locky;
				bool freeze;
				UINT32 dTime;

				explicit ORPCApplyPlayerAnimation() : ORPC(86) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wPlayerID);
					bs->Write(AnimLibLength);
					bs->Write(AnimLib, AnimLibLength);
					bs->Write(AnimNameLength);
					bs->Write(AnimName, AnimNameLength);
					bs->Write(fDelta);
					bs->Write(loop);
					bs->Write(lockx);
					bs->Write(locky);
					bs->Write(freeze);
					bs->Write(dTime);
				}
			};

			struct ORPCClearPlayerAnimation : public ORPC {
				UINT16 wPlayerID;

				explicit ORPCClearPlayerAnimation() : ORPC(87) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wPlayerID);
				}
			};

			struct ORPCDeathBroadcast : public ORPC {
				UINT16 wPlayerID;

				explicit ORPCDeathBroadcast() : ORPC(166) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wPlayerID);
				}
			};

			struct ORPCSetPlayerName : public ORPC {
				UINT16 wPlayerID;
				UINT8 NameLength;
				char Name[256];  // Assumindo que o nome do jogador não ultrapasse 255 caracteres
				UINT8 bSuccess;

				explicit ORPCSetPlayerName() : ORPC(11) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wPlayerID);
					bs->Write(NameLength);
					bs->Write(Name, NameLength);
					bs->Write(bSuccess);
				}
			};

			struct ORPCSetPlayerPos : public ORPC {
				float x, y, z;

				explicit ORPCSetPlayerPos() : ORPC(12) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(x);
					bs->Write(y);
					bs->Write(z);
				}
			};

			struct ORPCSetPlayerPosFindZ : public ORPC {
				float x, y, z;

				explicit ORPCSetPlayerPosFindZ() : ORPC(13) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(x);
					bs->Write(y);
					bs->Write(z);
				}
			};

			struct ORPCSetPlayerFacingAngle : public ORPC {
				float angle;

				explicit ORPCSetPlayerFacingAngle() : ORPC(19) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(angle);
				}
			};

			struct ORPCSetPlayerSkillLevel : public ORPC {
				UINT16 wPlayerID;
				UINT32 dSkillID;
				UINT16 wLevel;

				explicit ORPCSetPlayerSkillLevel() : ORPC(34) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wPlayerID);
					bs->Write(dSkillID);
					bs->Write(wLevel);
				}
			};


			// SetPlayerTime - ID: 29
			struct ORPCSetPlayerTime : public ORPC {
				uint8_t hour, minute;

				explicit ORPCSetPlayerTime() : ORPC(29) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(hour);
					bs->Write(minute);
				}
			};

			struct ORPCSetPlayerSpecialAction : public ORPC {
				uint8_t bActionID;

				explicit ORPCSetPlayerSpecialAction() : ORPC(88) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(bActionID);
				}
			};

			struct ORPCSetWeather : public ORPC {
				uint8_t bWeatherID;

				explicit ORPCSetWeather() : ORPC(152) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(bWeatherID);
				}
			};

			struct ORPCSetWorldBounds : public ORPC {
				float max_x, min_x, max_y, min_y;

				explicit ORPCSetWorldBounds() : ORPC(17) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(max_x);
					bs->Write(min_x);
					bs->Write(max_y);
					bs->Write(min_y);
				}
			};

			struct ORPCSetPlayerVelocity : public ORPC {
				float x, y, z;

				explicit ORPCSetPlayerVelocity() : ORPC(90) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(x);
					bs->Write(y);
					bs->Write(z);
				}
			};

			struct ORPCSetPlayerSkin : public ORPC {
				UINT32 wPlayerID;
				UINT32 dSkinID;

				explicit ORPCSetPlayerSkin() : ORPC(153) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wPlayerID);
					bs->Write(dSkinID);
				}
			};



			struct ORPCTogglePlayerControllable : public ORPC {
				uint8_t moveable;

				explicit ORPCTogglePlayerControllable() : ORPC(15) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(moveable);
				}
			};

			struct ORPCTogglePlayerSpectating : public ORPC {
				uint32_t spectating;

				explicit ORPCTogglePlayerSpectating() : ORPC(124) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(spectating);
				}
			};

			struct ORPCToggleClock : public ORPC {
				uint8_t toggle;

				explicit ORPCToggleClock() : ORPC(30) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(toggle);
				}
			};

			struct ORPCSetPlayerTeam : public ORPC {
				uint16_t wPlayerID;
				uint8_t bTeamID;

				explicit ORPCSetPlayerTeam() : ORPC(69) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wPlayerID);
					bs->Write(bTeamID);
				}
			};

			struct ORPCPlaySound : public ORPC {
				uint32_t soundid;
				float x, y, z;

				explicit ORPCPlaySound() : ORPC(16) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(soundid);
					bs->Write(x);
					bs->Write(y);
					bs->Write(z);
				}
			};

			struct ORPCGivePlayerMoney : public ORPC {
				int32_t iMoney;

				explicit ORPCGivePlayerMoney() : ORPC(18) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(iMoney);
				}
			};

			struct ORPCResetPlayerMoney : public ORPC {
				explicit ORPCResetPlayerMoney() : ORPC(20) {}

				void Write(RakNet::BitStream* bs) override {}
			};

			struct ORPCResetPlayerWeapons : public ORPC {
				explicit ORPCResetPlayerWeapons() : ORPC(21) {}

				void Write(RakNet::BitStream* bs) override {}
			};

			struct ORPCGivePlayerWeapon : public ORPC {
				uint32_t dWeaponID, dBullets;

				explicit ORPCGivePlayerWeapon() : ORPC(22) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(dWeaponID);
					bs->Write(dBullets);
				}
			};

			struct ORPCPlayAudioStream : public ORPC {
				uint8_t UrlLength;
				char* Url;
				float x, y, z, radius;
				uint8_t UsePos;

				explicit ORPCPlayAudioStream() : ORPC(41) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(UrlLength);
					bs->Write(Url, UrlLength);
					bs->Write(x);
					bs->Write(y);
					bs->Write(z);
					bs->Write(radius);
					bs->Write(UsePos);
				}
			};

			struct ORPCPlayCrimeReport : public ORPC {
				uint16_t suspectId;
				uint32_t inVehicle, vehicleModel, vehicleColor, crime;
				float x, y, z;

				explicit ORPCPlayCrimeReport() : ORPC(112) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(suspectId);
					bs->Write(inVehicle);
					bs->Write(vehicleModel);
					bs->Write(vehicleColor);
					bs->Write(crime);
					bs->Write(x);
					bs->Write(y);
					bs->Write(z);
				}
			};

			struct ORPCStopAudioStream : public ORPC {
				explicit ORPCStopAudioStream() : ORPC(42) {}

				void Write(RakNet::BitStream* bs) override {}
			};

			struct ORPCRemoveBuilding : public ORPC {
				uint32_t dObjectModel;
				float x, y, z, radius;

				explicit ORPCRemoveBuilding() : ORPC(43) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(dObjectModel);
					bs->Write(x);
					bs->Write(y);
					bs->Write(z);
					bs->Write(radius);
				}
			};

			struct ORPCSetPlayerHealth : public ORPC {
				float health;

				explicit ORPCSetPlayerHealth() : ORPC(14) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(health);
				}
			};

			struct ORPCSetPlayerArmour : public ORPC {
				float armour;

				explicit ORPCSetPlayerArmour() : ORPC(66) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(armour);
				}
			};

			struct ORPCSetWeaponAmmo : public ORPC {
				UINT8 bWeaponID;
				UINT16 wAmmo;

				explicit ORPCSetWeaponAmmo() : ORPC(145) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(bWeaponID);
					bs->Write(wAmmo);
				}
			};

			struct ORPCSetCameraBehind : public ORPC {
				explicit ORPCSetCameraBehind() : ORPC(162) {}

				void Write(RakNet::BitStream* bs) override {
					// No parameters to write
				}
			};

			struct ORPCSetArmedWeapon : public ORPC {
				UINT32 dWeaponID;

				explicit ORPCSetArmedWeapon() : ORPC(67) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(dWeaponID);
				}
			};

			struct ORPCWorldPlayerAdd : public ORPC {
				UINT16 wPlayerID;
				UINT8 team;
				UINT32 dSkinId;
				float PosX, PosY, PosZ;
				float facing_angle;
				UINT32 player_color;
				UINT8 fighting_style;
				UINT16 wSkillLevel[11];

				explicit ORPCWorldPlayerAdd() : ORPC(32) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wPlayerID);
					bs->Write(team);
					bs->Write(dSkinId);
					bs->Write(PosX);
					bs->Write(PosY);
					bs->Write(PosZ);
					bs->Write(facing_angle);
					bs->Write(player_color);
					bs->Write(fighting_style);
					for (UINT8 i = 0; i < 11; i++) {
						bs->Write(wSkillLevel[i]);
					}
				}
			};

			struct ORPCWorldPlayerRemove : public ORPC {
				UINT16 wPlayerID;

				explicit ORPCWorldPlayerRemove() : ORPC(163) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wPlayerID);
				}
			};

			struct ORPCInterpolateCamera : public ORPC {
				bool bPosSet;
				float fromPosX, fromPosY, fromPosZ;
				float toPosX, toPosY, toPosZ;
				UINT32 time;
				UINT8 cutType;

				explicit ORPCInterpolateCamera() : ORPC(82) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(bPosSet);
					bs->Write(fromPosX);
					bs->Write(fromPosY);
					bs->Write(fromPosZ);
					bs->Write(toPosX);
					bs->Write(toPosY);
					bs->Write(toPosZ);
					bs->Write(time);
					bs->Write(cutType);
				}
			};

			struct ORPCCreateExplosion : public ORPC {
				float X, Y, Z;
				UINT32 wType;
				float radius;

				explicit ORPCCreateExplosion() : ORPC(79) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(X);
					bs->Write(Y);
					bs->Write(Z);
					bs->Write(wType);
					bs->Write(radius);
				}
			};

			struct ORPCSendDeathMessage : public ORPC {
				UINT16 wKillerID;
				UINT16 wPlayerID;
				UINT8 reason;

				explicit ORPCSendDeathMessage() : ORPC(55) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wKillerID);
					bs->Write(wPlayerID);
					bs->Write(reason);
				}
			};

			struct ORPCSendGameTimeUpdate : public ORPC {
				INT32 time;

				explicit ORPCSendGameTimeUpdate() : ORPC(60) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(time);
				}
			};

			struct ORPCSendClientMessage : public ORPC {
				UINT32 dColor;
				UINT32 dMessageLength;
				char Message[1024]; // Ajustar tamanho conforme necessário

				explicit ORPCSendClientMessage() : ORPC(93) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(dColor);
					bs->Write(dMessageLength);
					bs->Write(Message, dMessageLength);
				}
			};

			struct ORPCSetShopName : public ORPC {
				UINT32 length;
				char Name[256]; // Ajustar tamanho conforme necessário

				explicit ORPCSetShopName() : ORPC(33) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(length);
					bs->Write(Name, length);
				}
			};

			struct ORPCSetPlayerDrunkLevel : public ORPC {
				INT32 iDrunkLevel;

				explicit ORPCSetPlayerDrunkLevel() : ORPC(35) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(iDrunkLevel);
				}
			};

			struct ORPCSetPlayerFightingStyle : public ORPC {
				UINT16 wPlayerID;
				UINT8 fightstyle;

				explicit ORPCSetPlayerFightingStyle() : ORPC(89) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wPlayerID);
					bs->Write(fightstyle);
				}
			};

			struct ORPCSetInterior : public ORPC {
				UINT8 bInteriorID;

				explicit ORPCSetInterior() : ORPC(156) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(bInteriorID);
				}
			};

			struct ORPCSetPlayerColor : public ORPC {
				UINT16 wPlayerID;
				UINT32 dColor;

				explicit ORPCSetPlayerColor() : ORPC(72) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wPlayerID);
					bs->Write(dColor);
				}
			};

			struct ORPCForceClassSelection : public ORPC {
				explicit ORPCForceClassSelection() : ORPC(74) {}

				void Write(RakNet::BitStream* bs) override {
					// No parameters to write
				}
			};

			struct ORPCToggleWidescreen : public ORPC {
				UINT8 enable;

				explicit ORPCToggleWidescreen() : ORPC(111) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(enable);
				}
			};

			struct ORPCSetPlayerWantedLevel : public ORPC {
				UINT8 bWantedLevel;

				explicit ORPCSetPlayerWantedLevel() : ORPC(133) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(bWantedLevel);
				}
			};

			struct ORPCSetCameraPos : public ORPC {
				float lookposX, lookposY, lookposZ;

				explicit ORPCSetCameraPos() : ORPC(157) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(lookposX);
					bs->Write(lookposY);
					bs->Write(lookposZ);
				}
			};

			struct ORPCSetCameraLookAt : public ORPC {
				float lookposX, lookposY, lookposZ;
				UINT8 cutType;

				explicit ORPCSetCameraLookAt() : ORPC(158) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(lookposX);
					bs->Write(lookposY);
					bs->Write(lookposZ);
					bs->Write(cutType);
				}
			};

			struct ORPCSetSpawnInfo : public ORPC {
				UINT8 byteTeam;
				UINT32 dSkin;
				UINT8 unused;
				float X, Y, Z;
				float fRotation;
				UINT32 dSpawnWeapons1, dSpawnWeapons2, dSpawnWeapons3;
				UINT32 dSpawnWeaponsAmmo1, dSpawnWeaponsAmmo2, dSpawnWeaponsAmmo3;

				explicit ORPCSetSpawnInfo() : ORPC(68) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(byteTeam);
					bs->Write(dSkin);
					bs->Write(unused);
					bs->Write(X);
					bs->Write(Y);
					bs->Write(Z);
					bs->Write(fRotation);
					bs->Write(dSpawnWeapons1);
					bs->Write(dSpawnWeapons2);
					bs->Write(dSpawnWeapons3);
					bs->Write(dSpawnWeaponsAmmo1);
					bs->Write(dSpawnWeaponsAmmo2);
					bs->Write(dSpawnWeaponsAmmo3);
				}
			};

			struct ORPCRequestClass : public ORPC {
				UINT8 bRequestResponse;
				UINT8 byteTeam;
				UINT32 dSkin;
				UINT8 unused;
				float X, Y, Z;
				float fRotation;
				UINT32 dSpawnWeapons1, dSpawnWeapons2, dSpawnWeapons3;
				UINT32 dSpawnWeaponsAmmo1, dSpawnWeaponsAmmo2, dSpawnWeaponsAmmo3;

				explicit ORPCRequestClass() : ORPC(128) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(bRequestResponse);
					bs->Write(byteTeam);
					bs->Write(dSkin);
					bs->Write(unused);
					bs->Write(X);
					bs->Write(Y);
					bs->Write(Z);
					bs->Write(fRotation);
					bs->Write(dSpawnWeapons1);
					bs->Write(dSpawnWeapons2);
					bs->Write(dSpawnWeapons3);
					bs->Write(dSpawnWeaponsAmmo1);
					bs->Write(dSpawnWeaponsAmmo2);
					bs->Write(dSpawnWeaponsAmmo3);
				}
			};

			struct ORPCRequestSpawn : public ORPC {
				UINT8 bRequestResponse;

				explicit ORPCRequestSpawn() : ORPC(129) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(bRequestResponse);
				}
			};

			struct ORPCSpectatePlayer : public ORPC {
				UINT16 wPlayerID;
				UINT8 bSpecCamType;

				explicit ORPCSpectatePlayer() : ORPC(126) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wPlayerID);
					bs->Write(bSpecCamType);
				}
			};

			struct ORPCSpectateVehicle : public ORPC {
				UINT16 wVehicleID;
				UINT8 bSpecCamType;

				explicit ORPCSpectateVehicle() : ORPC(127) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wVehicleID);
					bs->Write(bSpecCamType);
				}
			};

			struct ORPCEnableStuntBonus : public ORPC {
				UINT8 enable;

				explicit ORPCEnableStuntBonus() : ORPC(104) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(enable);
				}
			};

			struct ORPCToggleSelectTextDraw : public ORPC {
				UINT8 enable;
				UINT32 color;

				explicit ORPCToggleSelectTextDraw() : ORPC(83) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(enable);
					bs->Write(color);
				}
			};


			struct ORPCTextDrawSetString : public ORPC {
				UINT16 wTextDrawID;
				UINT16 TextLength;
				char Text[4096]; // Máximo de 4096 caracteres

				explicit ORPCTextDrawSetString() : ORPC(105) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wTextDrawID);
					bs->Write(TextLength);
					bs->Write(Text, TextLength);
				}
			};

			struct ORPCShowTextDraw : public ORPC {
				UINT16 wTextDrawID;
				UINT8 Flags;
				float fLetterWidth, fLetterHeight;
				UINT32 dLetterColor;
				float fLineWidth, fLineHeight;
				UINT32 dBoxColor;
				UINT8 Shadow, Outline;
				UINT32 dBackgroundColor;
				UINT8 Style, Selectable;
				float fX, fY;
				UINT16 wModelID;
				float fRotX, fRotY, fRotZ;
				float fZoom;
				INT16 wColor1, wColor2;
				UINT16 szTextLen;
				char szText[4096]; // Máximo de 4096 caracteres

				explicit ORPCShowTextDraw() : ORPC(134) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wTextDrawID);
					bs->Write(Flags);
					bs->Write(fLetterWidth);
					bs->Write(fLetterHeight);
					bs->Write(dLetterColor);
					bs->Write(fLineWidth);
					bs->Write(fLineHeight);
					bs->Write(dBoxColor);
					bs->Write(Shadow);
					bs->Write(Outline);
					bs->Write(dBackgroundColor);
					bs->Write(Style);
					bs->Write(Selectable);
					bs->Write(fX);
					bs->Write(fY);
					bs->Write(wModelID);
					bs->Write(fRotX);
					bs->Write(fRotY);
					bs->Write(fRotZ);
					bs->Write(fZoom);
					bs->Write(wColor1);
					bs->Write(wColor2);
					bs->Write(szTextLen);
					bs->Write(szText, szTextLen);
				}
			};
			
			struct ORPCHideTextDraw : public ORPC {
				UINT16 wTextDrawID;

				explicit ORPCHideTextDraw() : ORPC(135) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wTextDrawID);
				}
			};

			struct ORPCPlayerEnterVehicle : public ORPC {
				UINT16 wPlayerID;
				UINT16 wVehicleID;
				UINT8 bIsPassenger;

				explicit ORPCPlayerEnterVehicle() : ORPC(26) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wPlayerID);
					bs->Write(wVehicleID);
					bs->Write(bIsPassenger);
				}
			};

			struct ORPCPlayerExitVehicle : public ORPC {
				UINT16 wPlayerID;
				UINT16 wVehicleID;

				explicit ORPCPlayerExitVehicle() : ORPC(154) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wPlayerID);
					bs->Write(wVehicleID);
				}
			};

			struct ORPCRemoveVehicleComponent : public ORPC {
				UINT16 wVehicleID;
				UINT16 wComponentID;

				explicit ORPCRemoveVehicleComponent() : ORPC(57) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wVehicleID);
					bs->Write(wComponentID);
				}
			};

			struct ORPCAttachTrailerToVehicle : public ORPC {
				UINT16 wTrailerID;
				UINT16 wVehicleID;

				explicit ORPCAttachTrailerToVehicle() : ORPC(148) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wTrailerID);
					bs->Write(wVehicleID);
				}
			};

			struct ORPCDetachTrailerFromVehicle : public ORPC {
				UINT16 wVehicleID;

				explicit ORPCDetachTrailerFromVehicle() : ORPC(149) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wVehicleID);
				}
			};

			struct ORPCLinkVehicleToInterior : public ORPC {
				UINT16 wVehicleID;
				UINT8 bInteriorID;

				explicit ORPCLinkVehicleToInterior() : ORPC(65) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wVehicleID);
					bs->Write(bInteriorID);
				}
			};
			
			struct ORPCPutPlayerInVehicle : public ORPC {
				UINT16 wVehicleID;
				UINT8 bSeatID;

				explicit ORPCPutPlayerInVehicle() : ORPC(70) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wVehicleID);
					bs->Write(bSeatID);
				}
			};

			struct ORPCRemovePlayerFromVehicle : public ORPC {
				// Nenhum parâmetro necessário para esse RPC.
				explicit ORPCRemovePlayerFromVehicle() : ORPC(71) {}

				void Write(RakNet::BitStream* bs) override {
					// Não há dados para escrever, apenas envie o RPC.
				}
			};

			struct ORPCUpdateVehicleDamageStatus : public ORPC {
				UINT16 wVehicleID;
				UINT32 panels;
				UINT32 doors;
				UINT8 lights;
				UINT8 tires;

				explicit ORPCUpdateVehicleDamageStatus() : ORPC(106) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wVehicleID);
					bs->Write(panels);
					bs->Write(doors);
					bs->Write(lights);
					bs->Write(tires);
				}
			};

			struct ORPCSetVehicleTireStatus : public ORPC {
				UINT16 wVehicleID;
				UINT8 tires;

				explicit ORPCSetVehicleTireStatus() : ORPC(98) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wVehicleID);
					bs->Write(tires);
				}
			};

			struct ORPCScmEvent : public ORPC {
				UINT16 wPlayerID;
				UINT32 eventType;
				UINT32 wVehicleID;
				UINT32 param1;
				UINT32 param2;

				explicit ORPCScmEvent() : ORPC(96) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wPlayerID);
					bs->Write(eventType);
					bs->Write(wVehicleID);
					bs->Write(param1);
					bs->Write(param2);
				}
			};

			struct ORPCSetVehicleNumberPlate : public ORPC {
				UINT16 wVehicleID;
				UINT8 PlateLength;
				char PlateText[16];  // Adjust size accordingly to the maximum plate length

				explicit ORPCSetVehicleNumberPlate() : ORPC(123) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wVehicleID);
					bs->Write(PlateLength);
					bs->Write(PlateText, PlateLength);  // Write the plate text with the specified length
				}
			};
			
			struct ORPCDisableVehicleCollisions : public ORPC {
				bool disable;

				explicit ORPCDisableVehicleCollisions() : ORPC(167) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(disable);
				}
			};

			struct ORPCSetVehicleHealth : public ORPC {
				UINT16 wVehicleID;
				float Health;

				explicit ORPCSetVehicleHealth() : ORPC(147) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wVehicleID);
					bs->Write(Health);
				}
			};

			struct ORPCSetVehicleVelocity : public ORPC {
				UINT8 turn;  // 1 for angular velocity, 0 for linear velocity
				float x, y, z;

				explicit ORPCSetVehicleVelocity() : ORPC(91) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(turn);
					bs->Write(x);
					bs->Write(y);
					bs->Write(z);
				}
			};

			struct ORPCSetVehiclePos : public ORPC {
				UINT16 wVehicleID;
				float x, y, z;

				explicit ORPCSetVehiclePos() : ORPC(159) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wVehicleID);
					bs->Write(x);
					bs->Write(y);
					bs->Write(z);
				}
			};

			struct ORPCSetVehicleZAngle : public ORPC {
				UINT16 wVehicleID;
				float Angle;

				explicit ORPCSetVehicleZAngle() : ORPC(160) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wVehicleID);
					bs->Write(Angle);
				}
			};

			struct ORPCSetVehicleParams : public ORPC {
				UINT16 wVehicleID;
				UINT8 bObjective;
				UINT8 bDoorsLocked;

				explicit ORPCSetVehicleParams() : ORPC(161) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wVehicleID);
					bs->Write(bObjective);
					bs->Write(bDoorsLocked);
				}
			};

			struct ORPCSetVehicleParamsEx : public ORPC {
				UINT16 wVehicleID;
				UINT8 bEngine, bLights, bAlarm, bDoors, bBonnet, bBoot;
				UINT8 bObjective, bSiren, bDoorDriver, bDoorPassenger;
				UINT8 bDoorBackLeft, bDoorBackRight, bWindowDriver, bWindowPassenger;
				UINT8 bWindowBackLeft, bWindowBackRight;

				explicit ORPCSetVehicleParamsEx() : ORPC(24) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wVehicleID);
					bs->Write(bEngine);
					bs->Write(bLights);
					bs->Write(bAlarm);
					bs->Write(bDoors);
					bs->Write(bBonnet);
					bs->Write(bBoot);
					bs->Write(bObjective);
					bs->Write(bSiren);
					bs->Write(bDoorDriver);
					bs->Write(bDoorPassenger);
					bs->Write(bDoorBackLeft);
					bs->Write(bDoorBackRight);
					bs->Write(bWindowDriver);
					bs->Write(bWindowPassenger);
					bs->Write(bWindowBackLeft);
					bs->Write(bWindowBackRight);
				}
			};

			struct ORPCWorldVehicleAdd : public ORPC {
				UINT16 wVehicleID;
				UINT32 ModelID;
				float X, Y, Z, Angle;
				UINT8 InteriorColor1, InteriorColor2;
				float Health;
				UINT8 interior;
				UINT32 DoorDamageStatus, PanelDamageStatus;
				UINT8 LightDamageStatus, tireDamageStatus;
				UINT8 addSiren;
				UINT8 modslot[14];  // modslots 0-13
				UINT8 PaintJob;
				UINT32 BodyColor1, BodyColor2;

				explicit ORPCWorldVehicleAdd() : ORPC(164) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wVehicleID);
					bs->Write(ModelID);
					bs->Write(X);
					bs->Write(Y);
					bs->Write(Z);
					bs->Write(Angle);
					bs->Write(InteriorColor1);
					bs->Write(InteriorColor2);
					bs->Write(Health);
					bs->Write(interior);
					bs->Write(DoorDamageStatus);
					bs->Write(PanelDamageStatus);
					bs->Write(LightDamageStatus);
					bs->Write(tireDamageStatus);
					bs->Write(addSiren);
					for (int i = 0; i < 14; i++) {
						bs->Write(modslot[i]);
					}
					bs->Write(PaintJob);
					bs->Write(BodyColor1);
					bs->Write(BodyColor2);
				}
			};

			struct ORPCWorldVehicleRemove : public ORPC {
				UINT16 wVehicleID;

				explicit ORPCWorldVehicleRemove() : ORPC(165) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wVehicleID);
				}
			};

			struct ORPCCreate3DTextLabel : public ORPC {
				UINT16 wLabelID;
				UINT32 color;
				float x, y, z;
				float DrawDistance;
				UINT8 testLOS;
				UINT16 attachedPlayer;
				UINT16 attachedVehicle;
				char text[4096];  // Assuming maximum text length is 4096 characters

				explicit ORPCCreate3DTextLabel() : ORPC(36) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wLabelID);
					bs->Write(color);
					bs->Write(x);
					bs->Write(y);
					bs->Write(z);
					bs->Write(DrawDistance);
					bs->Write(testLOS);
					bs->Write(attachedPlayer);
					bs->Write(attachedVehicle);
					bs->Write(text, sizeof(text));  // Write the 3D text label
				}
			};

			struct ORPCDelete3DTextLabel : public ORPC {
				UINT16 wLabelID;

				explicit ORPCDelete3DTextLabel() : ORPC(58) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(wLabelID);
				}
			};
			
			struct ORPCSetWorldTime : public ORPC {
				UINT8 bHour;

				explicit ORPCSetWorldTime() : ORPC(94) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(bHour);
				}
			};

			struct ORPCToggleCameraTarget : public ORPC {
				bool bEnabled;

				explicit ORPCToggleCameraTarget() : ORPC(170) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(bEnabled);
				}
			};

			struct ORPCDisableCheckpoint : public ORPC {
				explicit ORPCDisableCheckpoint() : ORPC(37) {}

				void Write(RakNet::BitStream* bs) override {
					// Este RPC não possui parâmetros, apenas é enviado.
				}
			};

			struct ORPCSetRaceCheckpoint : public ORPC {
				UINT8 type;
				float X, Y, Z;
				float nextposX, nextposY, nextposZ;
				float radius;

				explicit ORPCSetRaceCheckpoint() : ORPC(38) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(type);
					bs->Write(X);
					bs->Write(Y);
					bs->Write(Z);
					bs->Write(nextposX);
					bs->Write(nextposY);
					bs->Write(nextposZ);
					bs->Write(radius);
				}
			};

			struct ORPCDisableRaceCheckpoint : public ORPC {
				explicit ORPCDisableRaceCheckpoint() : ORPC(39) {}

				void Write(RakNet::BitStream* bs) override {
					// Este RPC não possui parâmetros, apenas é enviado.
				}
			};
			
			struct ORPCSetCheckpoint : public ORPC {
				float x, y, z, radius;

				explicit ORPCSetCheckpoint() : ORPC(107) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(x);
					bs->Write(y);
					bs->Write(z);
					bs->Write(radius);
				}
			};

			struct ORPCChatBubble : public ORPC {
				UINT16 playerid;
				UINT32 color;
				float drawDistance;
				UINT32 expiretime;
				UINT8 textLength;
				char text[256];  // Ajuste o tamanho conforme necessário, ou use um ponteiro para gerenciar dinamicamente

				explicit ORPCChatBubble() : ORPC(59) {}

				void Write(RakNet::BitStream* bs) override {
					bs->Write(playerid);
					bs->Write(color);
					bs->Write(drawDistance);
					bs->Write(expiretime);
					bs->Write(textLength);
					bs->Write(text, textLength);  // Escreve o texto baseado no comprimento
				}
			};



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
					static void ChatBubble(const uint16_t playerid, const uint32_t color, const float drawDistance, const uint32_t expiretime, uint8_t textLength, char* text);
					static void DisableCheckpoint(const int playerid);
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