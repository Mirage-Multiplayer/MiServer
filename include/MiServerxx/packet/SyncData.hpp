#pragma once
#include <MiServerxx/types.h>

#define WINDOWS_IGNORE_PACKING_MISMATCH

namespace mimp
{
	namespace internal
	{
		namespace packet
		{
#pragma pack(push, 1)
			typedef struct _ONFOOT_SYNC_DATA
			{
				WORD lrAnalog;
				WORD udAnalog;
				WORD wKeys;
				float vecPos[3];
				float fQuaternion[4];
				BYTE byteHealth;
				BYTE byteArmour;
				BYTE byteCurrentWeapon;
				BYTE byteSpecialAction;
				float vecMoveSpeed[3];
				float vecSurfOffsets[3];
				WORD wSurfInfo;
				int iCurrentAnimationID;
			} ONFOOT_SYNC_DATA;
#pragma pack(pop)
#pragma pack(push, 1)
			typedef struct _INCAR_SYNC_DATA
			{
				WORD VehicleID;
				WORD lrAnalog;
				WORD udAnalog;
				WORD wKeys;
				float fQuaternion[4];
				float vecPos[3];
				float vecMoveSpeed[3];
				float fCarHealth;
				BYTE bytePlayerHealth;
				BYTE bytePlayerArmour;
				BYTE byteCurrentWeapon;
				BYTE byteSirenOn;
				BYTE byteLandingGearState;
				WORD TrailerID_or_ThrustAngle;
				FLOAT fTrainSpeed;
			} INCAR_SYNC_DATA;
#pragma pack(pop)
#pragma pack(push, 1)
			typedef struct _PASSENGER_SYNC_DATA
			{
				WORD VehicleID;
				BYTE byteSeatFlags : 7;
				BYTE byteDriveBy : 1;
				BYTE byteCurrentWeapon;
				BYTE bytePlayerHealth;
				BYTE bytePlayerArmour;
				WORD lrAnalog;
				WORD udAnalog;
				WORD wKeys;
				float vecPos[3];
			} PASSENGER_SYNC_DATA;
#pragma pack(pop)
#pragma pack(push, 1)

			enum eWeaponState
			{
				WS_NO_BULLETS = 0,
				WS_LAST_BULLET = 1,
				WS_MORE_BULLETS = 2,
				WS_RELOADING = 3,
			};
#pragma pack(pop)
#pragma pack(push, 1)

			typedef struct _AIM_SYNC_DATA
			{
				BYTE byteCamMode;
				float vecAimf1[3];
				float vecAimPos[3];
				float fAimZ;
				BYTE byteCamExtZoom : 6;  // 0-63 normalized
				BYTE byteWeaponState : 2; // see eWeaponState
				BYTE bUnk;
			} AIM_SYNC_DATA;
#pragma pack(pop)
#pragma pack(push, 1)
			typedef struct _UNOCCUPIED_SYNC_DATA // 67
			{
				WORD VehicleID;
				short cvecRoll[3];
				short cvecDirection[3];
				BYTE unk[13];
				float vecPos[3];
				float vecMoveSpeed[3];
				float vecTurnSpeed[3];
				float fHealth;
			} UNOCCUPIED_SYNC_DATA;
#pragma pack(pop)
#pragma pack(push, 1)
			typedef struct _SPECTATOR_SYNC_DATA
			{
				WORD lrAnalog;
				WORD udAnalog;
				WORD wKeys;
				float vecPos[3];
			} SPECTATOR_SYNC_DATA;
#pragma pack(pop)
#pragma pack(push, 1)
			typedef struct _BULLET_SYNC_DATA
			{
				BYTE bHitType;
				unsigned short iHitID;
				float fHitOrigin[3];
				float fHitTarget[3];
				float fCenterOfHit[3];
				BYTE bWeaponID;
			} BULLET_SYNC_DATA;
#pragma pack(pop)
#pragma pack(push, 1)
			typedef struct _PLAYER_SPAWN_INFO
			{
				BYTE byteTeam;
				int iSkin;
				BYTE unk;
				float vecPos[3];
				float fRotation;
				int iSpawnWeapons[3];
				int iSpawnWeaponsAmmo[3];
			} PLAYER_SPAWN_INFO;
#pragma pack(pop)
#pragma pack(push, 1)
			typedef struct _PICKUP
			{
				int iModel;
				int iType;
				float fX;
				float fY;
				float fZ;
			} PICKUP;
#pragma pack(pop)
#pragma pack(push, 1)
			typedef struct _TEXT_DRAW_TRANSMIT
			{
				union
				{
					BYTE byteFlags;
					struct
					{
						BYTE byteBox : 1;
						BYTE byteLeft : 1;
						BYTE byteRight : 1;
						BYTE byteCenter : 1;
						BYTE byteProportional : 1;
						BYTE bytePadding : 3;
					};
				};
				float fLetterWidth;
				float fLetterHeight;
				DWORD dwLetterColor;
				float fLineWidth;
				float fLineHeight;
				DWORD dwBoxColor;
				BYTE byteShadow;
				BYTE byteOutline;
				DWORD dwBackgroundColor;
				BYTE byteStyle;
				BYTE byteSelectable;
				float fX;
				float fY;
				WORD wModelID;
				float fRotX;
				float fRotY;
				float fRotZ;
				float fZoom;
				WORD wColor1;
				WORD wColor2;
			} TEXT_DRAW_TRANSMIT;
#pragma pack(pop)
#pragma pack(push, 1)
			typedef struct _NEW_VEHICLE
			{
				WORD VehicleId;
				int iVehicleType;
				float vecPos[3];
				float fRotation;
				BYTE aColor1;
				BYTE aColor2;
				float fHealth;
				BYTE byteInterior;
				DWORD dwDoorDamageStatus;
				DWORD dwPanelDamageStatus;
				BYTE byteLightDamageStatus;
				BYTE byteTireDamageStatus;
				BYTE byteAddSiren;
				BYTE byteModSlots[14];
				BYTE bytePaintjob;
				DWORD cColor1;
				DWORD cColor2;
			} NEW_VEHICLE;
#pragma pack(pop)
#pragma pack(push, 1)
			struct stPlayerInfo
			{
				int iIsConnected;
				int iIsStreamedIn;
				int iGotMarkersPos;
				char szPlayerName[20];
				int iScore;
				DWORD dwPing;
				int iAreWeInAVehicle;
				BYTE byteInteriorId;
				BYTE byteIsNPC;

				// STORED INFO
				ONFOOT_SYNC_DATA onfootData;
				INCAR_SYNC_DATA incarData;
				PASSENGER_SYNC_DATA passengerData;
				AIM_SYNC_DATA aimData;
				UNOCCUPIED_SYNC_DATA unocData;
				BULLET_SYNC_DATA bulletData;
			};
#pragma pack(pop)
		}
	}
}