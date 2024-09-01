#ifndef __MISERVER_EVENTTYPES_HPP
#define __MISERVER_EVENTTYPES_HPP
#include <functional>
#include <MiServer/netgame/Player.hpp>
#include <MiServer/netgame/Vehicle.hpp>

/* EventType
	Store information about events, their callbacks and their params
*/
namespace mimp
{
	namespace internal
	{
		namespace event
		{
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

			// Disclaimer: I wanted to make this as dynamic as possible, and this was the way I found
			using OnServerInit_t = std::function<int()>;

			using OnServerExit_t = std::function<int()>;

			using OnPlayerConnect_t = std::function<int(Player *)>;
			using OnPlayerConnect_params = struct
			{
				Player *player;
			};

			using OnPlayerDisconnect_t = std::function<int(Player *, const int)>;
			using OnPlayerDisconnect_params = struct
			{
				Player *player;
				const int reason;
			};

			using OnPlayerSpawn_t = std::function<int(Player *)>;
			using OnPlayerSpawn_params = struct
			{
				Player *player;
			};

			using OnPlayerUpdate_t = std::function<int(Player *)>;
			using OnPlayerUpdate_params = struct
			{
				Player *player;
			};
			using OnPlayerDeath_t = std::function<int(Player *, Player *, const int)>;
			using OnPlayerDeath_params = struct
			{
				Player *player;
				Player *killer;
				const int reason;
			};

			using OnVehicleSpawn_t = std::function<int(Vehicle *)>;
			using OnVehicleSpawn_params = struct
			{
				Vehicle *vehicle;
			};

			using OnVehicleDeath_t = std::function<int(Vehicle *, Player *)>;
			using OnVehicleDeath_params = struct
			{
				Vehicle *vehicle;
				Player *killer;
			};

			using OnPlayerText_t = std::function<int(Player *, const char *)>;
			using OnPlayerText_params = struct
			{
				Player *player;
				const char *text;
			};

			using OnPlayerCommandText_t = std::function<int(Player *, const char *)>;
			using OnPlayerCommandText_params = struct
			{
				Player *player;
				const char *cmd;
			};

			using OnPlayerRequestClass_t = std::function<int(Player *, const int)>;
			using OnPlayerRequestClass_params = struct
			{
				Player *player;
				const int classid;
			};

			using OnPlayerEnterVehicle_t = std::function<int(Player *, Vehicle *)>;
			using OnPlayerEnterVehicle_params = struct
			{
				Player *player;
				Vehicle *vehicle;
			};

			using OnPlayerExitVehicle_t = std::function<int(Player *, Vehicle *)>;
			using OnPlayerExitVehicle_params = struct
			{
				Player *player;
				Vehicle *vehicle;
			};

			using OnPlayerStateChange_t = std::function<int(Player *, const int, const int)>;
			using OnPlayerStateChange = struct
			{
				Player *player;
				const int newstate;
				const int oldstate;
			};

			using OnPlayerEnterCheckpoint_t = std::function<int(Player *)>;
			using OnPlayerEnterCheckpoint_params = struct
			{
				Player *player;
			};

			using OnPlayerLeaveCheckpoint_t = std::function<int(Player *)>;
			using OnPlayerLeaveCheckpoint_params = struct
			{
				Player *player;
			};

			using OnPlayerEnterRaceCheckpoint_t = std::function<int(Player *)>;
			using OnPlayerEnterRaceCheckpoint_params = struct
			{
				Player *player;
			};

			using OnPlayerLeaveRaceCheckpoint_t = std::function<int(Player *)>;
			using OnPlayerLeaveRaceCheckpoint_params = struct
			{
				Player *player;
			};

			using OnRconCommand_t = std::function<int(const char *)>;
			using OnRconCommand_params = struct
			{
				const char *cmd;
			};

		}
	}
}
#endif