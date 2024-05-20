
///////////////////////////////////////////////////////////////////////////
// 
// Copyright(c) 2024, Apperoso Ltd
// All rights reserved.
//
// This source code is licensed under the BSD - style license found in the
// LICENSE file in the root directory of this source tree.
// 
///////////////////////////////////////////////////////////////////////////

#pragma once

#include "vehicle_database/demo/all_Vehicles.h"
#include <vector>

namespace apperoso {

	using Bicycles = std::vector<Bicycle>;
	using Cars = std::vector<Car>;
	using Planes = std::vector<Plane>;
	using Trucks = std::vector<Truck>;

	Bicycles makeBicycles();
	Cars makeCars();
	Planes makePlanes();
	Trucks makeTrucks();
}
