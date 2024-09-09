#include <MiServer/netgame/Vehicle.hpp>
#include <MiServer/packet/SyncData.hpp>
#include <MiServer/netgame/NetGame.hpp>
#include <MiServer/server/ServerInstance.hpp>
#include <MiServer/server/Server.hpp>
#include <iostream>

mimp::CVehicle::CVehicle()
	: m_vehId(0), m_modelId(0), m_interiorId(0), m_health(100.0f),
	  m_rotation(0.0f), m_color1(0), m_color2(0), m_static(false),
	  m_respawn(false), m_timeUntilRespawn(0)
{
	this->m_pos[0] = 0.0f;
	this->m_pos[1] = 0.0f;
	this->m_pos[2] = 0.0f;
}

void mimp::CVehicle::setHealth(const float value)
{
	this->m_health = value;
}

void mimp::CVehicle::setPosition(const float x, const float y, const float z)
{
	this->m_pos[0] = x;
	this->m_pos[1] = y;
	this->m_pos[2] = z;
}

void mimp::CVehicle::respawn(void)
{
	mimp::internal::RPC::outgoing::Handler::WorldVehicleRemove(this->m_vehId, -1);
	mimp::internal::RPC::outgoing::Handler::WorldVehicleAdd(this, -1);
}

int mimp::CVehicle::Create(const uint16_t model, const float x, const float y, const float z, const float rotation,
						   const int color1, const int color2, const int respawndelay, const bool respawn, const bool siren, const int interior)
{
	CVehicle *veh = new CVehicle();
	veh->m_health = 1000.0f;
	veh->m_modelId = model;
	veh->m_pos[0] = x;
	veh->m_pos[1] = y;
	veh->m_pos[2] = z;

	veh->m_rotation = rotation;

	veh->m_color1 = color1;
	veh->m_color2 = color2;

	veh->m_timeUntilRespawn = respawndelay;
	veh->m_respawn = respawn;

	veh->m_static = false;

	veh->m_interiorId = interior;

	const int idx = mimp::internal::server::GetServerInstance()->GetNetGame()->GetVehiclePool()->Insert(veh);
	if (idx == -1)
	{
		return -1;
	}
	veh->m_vehId = idx;
	mimp::internal::RPC::outgoing::Handler::WorldVehicleAdd(veh, -1);

	return idx;
}
