
///////////////////////////////////////////////////////////////////////////
// 
// Copyright(c) 2024, Apperoso Ltd
// All rights reserved.
//
// This source code is licensed under the BSD - style license found in the
// LICENSE file in the root directory of this source tree.
// 
///////////////////////////////////////////////////////////////////////////

#include "vehicle_database/vehicles/bicycle.h"
#include <print>

namespace apperoso {

	PropertyStatus Bicycle::validateCommonProperty(VehiclePropertyToken /*propertyToken*/, std::string_view /*value*/) {
		return PropertyStatus::success;
	}

	PropertyStatus Bicycle::validateSpecificProperty(VehiclePropertyToken /*propertyToken*/, std::string_view /*value*/) {
		return PropertyStatus::success;
	}
}