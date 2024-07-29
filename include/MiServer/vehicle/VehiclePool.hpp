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
				VehiclePool(unsigned short max_vehicles);
				int Count() const;

				
				int Add(Vehicle* p);

				
				int Remove(const VEHICLEID id);

		
				Vehicle* Get(const VEHICLEID id);

				
				const bool IsValidVehicle(const VEHICLEID id) const;
			private:
				unsigned short m_MaxVehicles;
				std::vector<Vehicle*> m_Pool;
			};
		}
	}
}

#endif