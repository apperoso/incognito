
///////////////////////////////////////////////////////////////////////////
// 
// Copyright(c) 2024, Apperoso Ltd
// All rights reserved.
//
// This source code is licensed under the BSD - style license found in the
// LICENSE file in the root directory of this source tree.
// 
///////////////////////////////////////////////////////////////////////////

#include "vehicle_database/demo/demo.h"
#include "vehicle_database/demo/vehicle_factory.h"
#include "vehicle_database/Vehicles/vehicle.h"
#include <print>
#include <vector>

namespace apperoso {

	using Vehicles = std::vector<Vehicle>;

	Vehicles createVehicles()
	{
		std::println("\nCreating Vehicles");
		std::println("-----------------");

		Vehicles vehicles;

		vehicles.append_range(makeBicycles());
		vehicles.append_range(makeCars());
		vehicles.append_range(makePlanes());
		vehicles.append_range(makeTrucks());

		return vehicles;
	}

	void printVehicleDetails(Vehicle const& vehicle) {
		std::println("\nVehicle: [{}]", vehicle.name());
		for (auto const& entry : vehicle.getPropertyStrings()) {
			std::println("[{}] = [{}]", entry.first, entry.second);
		}
	}

	void printVehicleDetails(Vehicles const& vehicles) {

		std::println("\nVehicle Details");
		std::println("---------------");

		for (auto const& vehicle : vehicles)
		{
			printVehicleDetails(vehicle);
		}
	}

	void Demo()
	{
		Vehicles vehicles = createVehicles();

		printVehicleDetails(vehicles);
	}

}
