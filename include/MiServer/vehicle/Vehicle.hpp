#ifndef __MISERVER_VEHICLE_HPP
#define __MISERVER_VEHICLE_HPP

#include "../types.h"
#include "../RPC/RPC.hpp"
#include "../RPC/RPCList.hpp"
#include <cstdint>

namespace mimp {

	/**
	 * Vehicle object.
	 */
	class Vehicle {
	public:
		Vehicle() = default;

		inline const int getId(void) const {
			return this->m_vehId;
		}

		inline const int getModelId(void) const {
			return this->m_modelId;
		}

		inline const float getHealth(void) const {
			return this->m_health;
		};

		inline void getPosition(float& x, float& y, float& z) const {
			x = this->m_pos[0];
			y = this->m_pos[1];
			z = this->m_pos[2];
		}

		inline const float getRotation(void) const {
			return this->m_rotation;
		}

		static int Create(const uint16_t model, const float x, const const float y, const float z, const float rotation,
			const int color1, const int color2, const int respawndelay, const bool respawn, const bool siren, const bool isStatic, const int interior);

		static int Destroy(const Vehicle& vehicle);

	private:
		friend class internal::RPC::incomming::Handler;
		friend void internal::RPC::SpawnAllVehiclesForPlayer(PLAYERID playerID);
		
		int m_vehId;
		int m_modelId;
		int m_interiorId;
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