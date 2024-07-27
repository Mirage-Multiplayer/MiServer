#ifndef __MISERVER_VEHICLEPOOL_HPP
#define __MISERVER_VEHICLEPOOL_HPP
#include "Vehicle.hpp"
#include "defines.hpp"
#include "VehicleTypes.hpp"
#include <vector>

namespace mimp {
	namespace internal {
		namespace vehicle {
			class VehiclePool {
			public:
				VehiclePool() = default;
				VehiclePool(unsigned short max_vehicles);
				inline int Count() {
					int c = 0;
					for (Vehicle* elem : this->m_Pool) {
						if (elem != nullptr) {
							++c;
						}
					}
					return c;
				}

				inline int Add(Vehicle* p) {
					int c = this->Count();
					if (c == MAX_VEHICLES)
						return -1;

					VEHICLEID vehicleIDRet = c;
					this->m_Pool[c] = p;

					return c;
				}


				inline int Remove(const VEHICLEID id) {
					if (id < 0 || id >= this->m_MaxVehicles || this->m_Pool[id] == nullptr) {
						return -1;
					}
					delete this->m_Pool[id];
					this->m_Pool[id] = nullptr;
					return 1;
				}

				inline Vehicle* Get(const VEHICLEID id) {
					if (id < 0 || id >= this->m_MaxVehicles) {
						return nullptr;
					}

					return this->m_Pool.at(id);
				}

				inline const bool IsValidVehicle(const VEHICLEID id) const {
					if (id < 0 || id >= this->m_MaxVehicles) {
						return nullptr;
					}

					if (this->m_Pool[id] == nullptr) {
						return false;
					}
					return true;
				}
			private:
				unsigned short m_MaxVehicles;
				std::vector<Vehicle*> m_Pool;
			};
		}
	}
}
#endif