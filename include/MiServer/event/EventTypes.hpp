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
			// note: FUCK TEMPLATED VARIADIC ARGS I HATE U. :p
			using OnServerInit_t = std::function<int()>;

			using OnServerExit_t = std::function<int()>;

			using OnPlayerConnect_t = std::function<int(CPlayer *)>;
			using OnPlayerConnect_params = struct
			{
				CPlayer *player;
			};

			using OnPlayerDisconnect_t = std::function<int(CPlayer *, const int)>;
			using OnPlayerDisconnect_params = struct
			{
				CPlayer *player;
				const int reason;
			};

			using OnPlayerSpawn_t = std::function<int(CPlayer *)>;
			using OnPlayerSpawn_params = struct
			{
				CPlayer *player;
			};

			using OnPlayerUpdate_t = std::function<int(CPlayer *)>;
			using OnPlayerUpdate_params = struct
			{
				CPlayer *player;
			};
			using OnPlayerDeath_t = std::function<int(CPlayer *, CPlayer *, const int)>;
			using OnPlayerDeath_params = struct
			{
				CPlayer *player;
				CPlayer *killer;
				const int reason;
			};

			using OnVehicleSpawn_t = std::function<int(CVehicle *)>;
			using OnVehicleSpawn_params = struct
			{
				CVehicle *vehicle;
			};

			using OnVehicleDeath_t = std::function<int(CVehicle *, CPlayer *)>;
			using OnVehicleDeath_params = struct
			{
				CVehicle *vehicle;
				CPlayer *killer;
			};

			using OnPlayerText_t = std::function<int(CPlayer *, const char *)>;
			using OnPlayerText_params = struct
			{
				CPlayer *player;
				const char *text;
			};

			using OnPlayerCommandText_t = std::function<int(CPlayer *, const char *)>;
			using OnPlayerCommandText_params = struct
			{
				CPlayer *player;
				const char *cmd;
			};

			using OnPlayerRequestClass_t = std::function<int(CPlayer *, const int)>;
			using OnPlayerRequestClass_params = struct
			{
				CPlayer *player;
				const int classid;
			};

			using OnPlayerEnterVehicle_t = std::function<int(CPlayer *, CVehicle *)>;
			using OnPlayerEnterVehicle_params = struct
			{
				CPlayer *player;
				CVehicle *vehicle;
			};

			using OnPlayerExitVehicle_t = std::function<int(CPlayer *, CVehicle *)>;
			using OnPlayerExitVehicle_params = struct
			{
				CPlayer *player;
				CVehicle *vehicle;
			};

		}
	}
}
#endif