#include "vehicle/VehiclePool.hpp"

mimp::internal::vehicle::VehiclePool::VehiclePool(unsigned short max_vehicles): m_Pool(max_vehicles, nullptr) {
	this->m_MaxVehicles = max_vehicles;
}