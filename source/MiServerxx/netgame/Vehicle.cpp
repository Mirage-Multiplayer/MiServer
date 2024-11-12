#include <MiServerxx/netgame/Vehicle.hpp>
#include <MiServerxx/packet/SyncData.hpp>
#include <MiServerxx/netgame/NetGame.hpp>
#include <MiServerxx/core/CoreInstance.hpp>
#include <MiServerxx/core/Core.hpp>
#include <iostream>

using namespace mimp::internal::server;
using namespace mimp::internal::RPC;

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
	ORPCWorldVehicleRemove worldVehicleRemove;
	ORPCWorldVehicleAdd worldVehicleAdd;
	worldVehicleRemove.wVehicleID = this->m_vehId;

	worldVehicleAdd.addSiren = this->m_siren;
	worldVehicleAdd.Angle = this->m_rotation;
	worldVehicleAdd.BodyColor1 = this->m_color1;
	worldVehicleAdd.BodyColor2 = this->m_color2;
	worldVehicleAdd.DoorDamageStatus = 0;
	worldVehicleAdd.Health = this->m_health;
	worldVehicleAdd.interior = this->m_health;
	worldVehicleAdd.InteriorColor1 = 0;
	worldVehicleAdd.InteriorColor2 = 0;
	worldVehicleAdd.LightDamageStatus = 0;
	worldVehicleAdd.ModelID = this->m_modelId;
	memset(worldVehicleAdd.modslot, 0, 14);
	worldVehicleAdd.PaintJob = 0;
	worldVehicleAdd.PanelDamageStatus = 0;
	worldVehicleAdd.tireDamageStatus = 0;
	worldVehicleAdd.wVehicleID = this->m_vehId;
	worldVehicleAdd.X = this->m_pos[0];
	worldVehicleAdd.Y = this->m_pos[1];
	worldVehicleAdd.Z = this->m_pos[2];
	GetCoreInstance()->BroadcastRPC(&worldVehicleRemove);
	GetCoreInstance()->BroadcastRPC(&worldVehicleAdd);
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

	veh->m_siren = siren;

	const int idx = mimp::internal::server::GetCoreInstance()->GetNetGame()->GetVehiclePool()->Insert(veh);
	if (idx == -1)
	{
		return -1;
	}
	veh->m_vehId = idx;

	ORPCWorldVehicleAdd worldVehicleAdd;
	worldVehicleAdd.addSiren = siren;
	worldVehicleAdd.Angle = rotation;
	worldVehicleAdd.BodyColor1 = color1;
	worldVehicleAdd.BodyColor2 = color2;
	worldVehicleAdd.DoorDamageStatus = 0;
	worldVehicleAdd.Health = 1000.0f;
	worldVehicleAdd.interior = interior;
	worldVehicleAdd.InteriorColor1 = 0;
	worldVehicleAdd.InteriorColor2 = 0;
	worldVehicleAdd.LightDamageStatus = 0;
	worldVehicleAdd.ModelID = model;
	memset(worldVehicleAdd.modslot, 0, 14);
	worldVehicleAdd.PaintJob = 0;
	worldVehicleAdd.PanelDamageStatus = 0;
	worldVehicleAdd.tireDamageStatus = 0;
	worldVehicleAdd.wVehicleID = idx;
	worldVehicleAdd.X = x;
	worldVehicleAdd.Y = y;
	worldVehicleAdd.Z = z;

	GetCoreInstance()->BroadcastRPC(&worldVehicleAdd);
	return idx;
}
