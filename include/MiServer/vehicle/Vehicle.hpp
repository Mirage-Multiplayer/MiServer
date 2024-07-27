#ifndef __MISERVER_VEHICLE_HPP
#define __MISERVER_VEHICLE_HPP
#include "../types.h"
namespace mimp {
	struct Vehicle {
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