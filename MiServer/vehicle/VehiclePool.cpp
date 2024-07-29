#include "vehicle/VehiclePool.hpp"
#include "vehicle/Vehicle.hpp"

mimp::internal::vehicle::VehiclePool::VehiclePool(unsigned short max_vehicles): m_Pool(max_vehicles, nullptr) {
	this->m_MaxVehicles = max_vehicles;
}

int mimp::internal::vehicle::VehiclePool::Count() const {
	int c = 0;
	for (const Vehicle* elem : this->m_Pool) {
		if (elem != nullptr) {
			++c;
		}
	}
	return c;
}


int mimp::internal::vehicle::VehiclePool::Add(Vehicle* p) {
	int c = this->Count();
	if (c >= m_MaxVehicles) {
		return -1;
	}

	this->m_Pool[c] = p;
	return c;
}


int mimp::internal::vehicle::VehiclePool::Remove(const VEHICLEID id) {
	if (id < 0 || id >= m_MaxVehicles || this->m_Pool[id] == nullptr) {
		return -1;
	}

	delete this->m_Pool[id];
	this->m_Pool[id] = nullptr;
	return 1;
}


mimp::Vehicle* mimp::internal::vehicle::VehiclePool::Get(const VEHICLEID id) {
	if (id < 0 || id >= m_MaxVehicles) {
		return nullptr;
	}

	return this->m_Pool[id];
}


const bool mimp::internal::vehicle::VehiclePool::IsValidVehicle(const VEHICLEID id) const {
	if (id < 0 || id >= m_MaxVehicles) {
		return false;
	}

	if (this->m_Pool[id] == nullptr) {
		return false;
	}

	return true;
}