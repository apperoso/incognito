
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

#include "vehicle_database/enum_strings/all_vehicle_enum_strings.h"
#include "property_utils/property_token.h"

namespace apperoso {

	inline constexpr auto vehicleTokenFactory = PropertyTokenFactory<
		VehicleTypeEnum,
		CommonPropertyEnum,
		BicyclePropertyEnum,
		CarPropertyEnum,
		PlanePropertyEnum,
		TruckPropertyEnum
	>{};

}
