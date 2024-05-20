
///////////////////////////////////////////////////////////////////////////
// 
// Copyright(c) 2024, Apperoso Ltd
// All rights reserved.
//
// This source code is licensed under the BSD - style license found in the
// LICENSE file in the root directory of this source tree.
// 
///////////////////////////////////////////////////////////////////////////

#include "vehicle_database/vehicles/car.h"
#include <print>

namespace apperoso {

	PropertyStatus Car::validateCommonProperty(VehiclePropertyToken /*propertyToken*/, std::string_view /*value*/) {
		return PropertyStatus::success;
	}

	PropertyStatus Car::validateSpecificProperty(VehiclePropertyToken propertyToken, std::string_view value) {
		switch (toEnum<CarPropertyEnum>(propertyToken.propertyIndex())) {
		case CarPropertyEnum::door_count: return validateDoorCount(value);
		}
		return PropertyStatus::success;
	}

	PropertyStatus Car::validateDoorCount(std::string_view value)
	{
		if (value == "3" || value == "5") { return PropertyStatus::success; }

		std::println("[{}] ERROR - [{}] is not a valid door count", name(), value);
		return PropertyStatus::invalidValue;
	}

}