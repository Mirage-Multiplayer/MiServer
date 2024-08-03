#include "vehicle/Vehicle.hpp"
#include "packet/SyncData.hpp"
#include "vehicle/VehiclePool.hpp"
#include "server/ServerInstance.hpp"

int mimp::Vehicle::Create(const uint16_t model, const float x, const const float y, const float z, const float rotation,
	const int color1, const int color2, const int respawndelay, const bool respawn,  const bool siren, const bool isStatic, const int interior)
{
	Vehicle veh;
	veh.m_modelId = model;
	veh.m_pos[0] = x;
	veh.m_pos[1] = y;
	veh.m_pos[2] = z;

	veh.m_rotation = rotation;

	veh.m_color1 = color1;
	veh.m_color2 = color2;

	veh.m_timeUntilRespawn = respawndelay;
	veh.m_respawn = respawn;

	veh.m_static = isStatic;
	
	veh.m_interiorId = interior;

	const int idx = mimp::internal::server::GetServerInstance()->getVehiclePool()->Add(&veh);
	if (idx == -1) {
		return -1;
	}
	veh.m_vehId = idx;

	mimp::internal::packet::NEW_VEHICLE newVeh;
	newVeh.VehicleId = idx;
	newVeh.iVehicleType = model;
	newVeh.vecPos[0] = x;
	newVeh.vecPos[1] = y;
	newVeh.vecPos[2] = z;
	newVeh.fRotation = rotation;
	newVeh.fHealth = 1000.00f;
	newVeh.byteInterior = 0;
	newVeh.dwDoorDamageStatus = 0;
	newVeh.dwPanelDamageStatus = 0;
	newVeh.byteLightDamageStatus = 0;

	return idx;
}
