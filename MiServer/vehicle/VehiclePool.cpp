#include <MiServer/vehicle/VehiclePool.hpp>
#include <MiServer/vehicle/Vehicle.hpp>
#include <algorithm>

mimp::internal::vehicle::VehiclePool::VehiclePool(unsigned short max_vehicles) : m_Pool(max_vehicles, nullptr)
{
	this->m_MaxVehicles = max_vehicles;
}

int mimp::internal::vehicle::VehiclePool::Add(Vehicle *p)
{
	auto it = std::find(this->m_Pool.begin() + 1, this->m_Pool.end(), nullptr);
	if (it == this->m_Pool.end())
	{
		return -1;
	}
	size_t idx = std::distance(this->m_Pool.begin(), it);
	this->m_Pool[idx] = p;
	return idx;
}

int mimp::internal::vehicle::VehiclePool::Remove(const VEHICLEID id)
{
	if (id < 0 || id >= m_MaxVehicles || this->m_Pool[id] == nullptr)
	{
		return -1;
	}

	delete this->m_Pool[id];
	this->m_Pool[id] = nullptr;
	return 1;
}

mimp::Vehicle *mimp::internal::vehicle::VehiclePool::Get(const VEHICLEID id)
{
	if (id < 0 || id >= m_MaxVehicles)
	{
		return nullptr;
	}

	return this->m_Pool.at(id);
}

const bool mimp::internal::vehicle::VehiclePool::IsValidVehicle(const VEHICLEID id) const
{
	if (id < 0 || id >= m_MaxVehicles)
	{
		return false;
	}

	if (this->m_Pool.at(id) == nullptr)
	{
		return false;
	}

	return true;
}