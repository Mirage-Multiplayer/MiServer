#ifndef __MISERVER_VEHICLE_HPP
#define __MISERVER_VEHICLE_HPP

#include <MiServerxx/types.h>
#include <MiServerxx/RPC/RPC.hpp>
#include <MiServerxx/RPC/RPCList.hpp>
#include <cstdint>

namespace mimp
{

	/**
	 * Vehicle object.
	 */
	class CVehicle
	{
	public:
		CVehicle();

		inline const int getId(void) const
		{
			return this->m_vehId;
		}

		inline const int getModelId(void) const
		{
			return this->m_modelId;
		}

		inline const float getHealth(void) const
		{
			return this->m_health;
		};

		void setHealth(const float value);

		inline void getPosition(float &x, float &y, float &z) const
		{
			x = this->m_pos[0];
			y = this->m_pos[1];
			z = this->m_pos[2];
		}

		void setPosition(const float x, const float y, const float z);

		inline const float getRotation(void) const
		{
			return this->m_rotation;
		}

		inline const int getInterior(void) const
		{
			return this->m_interiorId;
		}

		inline const int getColor1(void) const
		{
			return this->m_color1;
		}

		inline const int getColor2(void) const
		{
			return this->m_color2;
		}

		inline const bool isStatic(void) const
		{
			return this->m_static;
		}

		inline const bool canRespawn(void) const
		{
			return this->m_respawn;
		}

		inline const bool hasSiren(void) const
		{
			return this->m_siren;
		}

		


		void respawn(void);

		static int Create(const uint16_t model, const float x, const float y, const float z, const float rotation,
						  const int color1, const int color2, const int respawndelay, const bool respawn, const bool siren, const int interior);

		static int Destroy(const CVehicle &vehicle);

	private:

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
		bool m_siren;
	};

}

#endif