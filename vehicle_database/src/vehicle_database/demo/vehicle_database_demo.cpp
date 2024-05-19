
///////////////////////////////////////////////////////////////////////////
// 
// Copyright(c) 2024, Apperoso Ltd
// All rights reserved.
//
// This source code is licensed under the BSD - style license found in the
// LICENSE file in the root directory of this source tree.
// 
///////////////////////////////////////////////////////////////////////////

#include "vehicle_database/demo/vehicle_database_demo.h"
#include "vehicle_database/demo/all_Vehicles.h"
#include "vehicle_database/Vehicles/vehicle.h"
#include <print>
#include <vector>

namespace apperoso {

	using Vehicles = std::vector<Vehicle>;

	void addBicycles(Vehicles& vehicles) {
		Vehicle bicycle1{ Bicycle() };
		bicycle1.setProperty(make, "Ribble");
		bicycle1.setProperty(color, "black");
		bicycle1.setProperty(bicycleBrakeType, "disc");
		bicycle1.setProperty(bicycleGearCount, "21");
		bicycle1.setProperty(bicycleStyle, "road");
		vehicles.push_back(bicycle1);
	}

	void addCars(Vehicles& vehicles) {
		Vehicle car1{ Car() };
		car1.setProperty(make, "Vauxhall");
		car1.setProperty(carStyle, "Hatchback");
		vehicles.push_back(car1);

		Vehicle car2{ Car() };
		car2.setProperty(make, "Ford");
		car2.setProperty(model, "Fiesta");
		car2.setProperty(color, "Blue");
		car2.setProperty(carStyle, "Estate");
		car2.setProperty(carDoorCount, "4"); // This is invalid
		vehicles.push_back(car2);
	}

	void addPlanes(Vehicles& vehicles) {
		Vehicle plane1{ Plane() };
		plane1.setProperty(color, "White");
		plane1.setProperty(planeEngineType, "Jet");
		plane1.setProperty(planeRange, "550 miles");
		vehicles.push_back(plane1);
	}

	void addTrucks(Vehicles& vehicles) {
		Vehicle truck1{ Truck() };
		truck1.setProperty(make, "Volvo");
		truck1.setProperty(truckLength, "26ft");
		truck1.setProperty(truckCapacity, "38 tonnes");
		vehicles.push_back(truck1);
	}

	void runVehicleDatabaseDemo()
	{
		Vehicles vehicles;
		addBicycles(vehicles);
		addCars(vehicles);
		addPlanes(vehicles);
		addTrucks(vehicles);

		//std::println("Car make = [{}]", *car.getProperty(make));
		//std::println("Car model = [{}]", *car.getProperty(model));
		//std::println("Car style = [{}]", *car.getProperty(carStyle));
	}

}
