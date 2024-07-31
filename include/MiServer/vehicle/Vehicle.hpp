#ifndef __MISERVER_VEHICLE_HPP
#define __MISERVER_VEHICLE_HPP

#include "../types.h"
#include "../RPC/RPC.hpp"
#include "../RPC/RPCList.hpp"

namespace mimp {

	class Vehicle {
	public:
		Vehicle() = default;
	private:
		friend class internal::RPC::incomming::Handler;
		friend void internal::RPC::SpawnAllVehiclesForPlayer(PLAYERID playerID);

		int m_modelId;
		float m_health;
		float m_roll[3];
		float m_dir[3];
		float m_pos[3];
		float m_rotation;
		BYTE m_color1;
		BYTE m_color2;
		bool m_static;
		int m_respawn;
		int m_timeUntilRespawn;
	};

}

#endif