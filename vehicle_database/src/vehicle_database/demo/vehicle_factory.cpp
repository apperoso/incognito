
///////////////////////////////////////////////////////////////////////////
// 
// Copyright(c) 2024, Apperoso Ltd
// All rights reserved.
//
// This source code is licensed under the BSD - style license found in the
// LICENSE file in the root directory of this source tree.
// 
///////////////////////////////////////////////////////////////////////////

#include "vehicle_database/demo/vehicle_factory.h"
#include <print>

namespace apperoso {

	Bicycles makeBicycles() {
		Bicycles bicycles;

		std::println("\nMaking Ribble bike");
		Bicycle ribble_bike{ "Ribble bike" };
		ribble_bike.setProperty(make, "Ribble");
		ribble_bike.setProperty(color, "black");
		ribble_bike.setProperty(bicycleBrakeType, "disc");
		ribble_bike.setProperty(bicycleGearCount, "21");
		ribble_bike.setProperty(bicycleStyle, "road");
		bicycles.push_back(ribble_bike);

		return bicycles;
	}

	Cars makeCars() {
		Cars cars;

		std::println("\nMaking Vauxhall car");
		Car vauxhall_car{ "Vauxhall car" };
		vauxhall_car.setProperty(make, "Vauxhall");
		vauxhall_car.setProperty(carStyle, "hatchback");
		cars.push_back(vauxhall_car);

		std::println("\nMaking Ford car");
		Car ford_car{ "Ford car" };
		ford_car.setProperty(make, "Ford");
		ford_car.setProperty(model, "Fiesta");
		ford_car.setProperty(color, "blue");
		ford_car.setProperty(carStyle, "estate");
		ford_car.setProperty(carDoorCount, "4"); // This is invalid
		cars.push_back(ford_car);

		return cars;
	}

	Planes makePlanes() {
		Planes planes;

		std::println("\nMaking Jet plane");
		Plane jet_plane{ "Jet plane" };
		jet_plane.setProperty(color, "white");
		jet_plane.setProperty(planeEngineType, "jet");
		jet_plane.setProperty(planeRange, "550 miles");
		planes.push_back(jet_plane);

		return planes;
	}

	Trucks makeTrucks() {
		Trucks trucks;

		std::println("\nMaking Volvo truck");
		Truck volvo_truck{ "Volvo truck" };
		volvo_truck.setProperty(make, "Volvo");
		volvo_truck.setProperty(truckLength, "26ft");
		volvo_truck.setProperty(truckCapacity, "38 tonnes");
		trucks.push_back(volvo_truck);

		return trucks;
	}

}
