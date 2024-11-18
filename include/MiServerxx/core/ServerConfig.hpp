#pragma once
#include <cstdint>
namespace mimp
{
	/**
	 * Server Configuration
	 */
	struct ServerConfig
	{
		bool zoneNames;
		bool useCJWalk;
		bool allowedWeapons;
		bool limitGlobalChatRadius;
		float globalChatRadius;
		bool stuntBonus;
		float nameTagDrawDistance;
		bool disableEnterExits;
		bool nameTagLOS;
		bool manualVehicleEngineAndLight;
		int spawnsAvailable;
		bool showPlayerTags;
		int showPlayerMarkers;
		uint8_t worldTime;
		uint8_t weather;
		float gravity;
		bool lanMode;
		int deathDropMoney;
		bool instagib;
		int netModeNormalOnfootSendRate;
		int netModeNormalIncarSendRate;
		int netModeFiringSendRate;
		int netModeSendMultiplier;
		uint8_t lagCompensation;
		ServerConfig()
			: zoneNames(true),
			  useCJWalk(true),
			  allowedWeapons(true),
			  limitGlobalChatRadius(false),
			  globalChatRadius(200.00f),
			  stuntBonus(false),
			  nameTagDrawDistance(70.0f),
			  disableEnterExits(false),
			  nameTagLOS(true),
			  manualVehicleEngineAndLight(false),
			  spawnsAvailable(1),
			  showPlayerTags(true),
			  showPlayerMarkers(1),
			  worldTime(12),
			  weather(10),
			  gravity(0.008f),
			  lanMode(false),
			  deathDropMoney(0),
			  instagib(false),
			  netModeNormalOnfootSendRate(40),
			  netModeNormalIncarSendRate(40),
			  netModeFiringSendRate(40),
			  netModeSendMultiplier(10),
			  lagCompensation(1) {}
	};
}
