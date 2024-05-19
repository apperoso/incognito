
///////////////////////////////////////////////////////////////////////////
// 
// Copyright(c) 2024, Apperoso Ltd
// All rights reserved.
//
// This source code is licensed under the BSD - style license found in the
// LICENSE file in the root directory of this source tree.
// 
///////////////////////////////////////////////////////////////////////////

#include "vehicle_database/vehicles/truck.h"
#include <print>

namespace apperoso {

	PropertyStatus Truck::validateCommonProperty(VehiclePropertyToken /*propertyToken*/, std::string_view /*value*/) {
		return PropertyStatus::success;
	}

	PropertyStatus Truck::validateSpecificProperty(VehiclePropertyToken /*propertyToken*/, std::string_view /*value*/) {
		return PropertyStatus::success;
	}
}