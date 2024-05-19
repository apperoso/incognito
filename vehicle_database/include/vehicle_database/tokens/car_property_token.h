
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

#include "vehicle_database/tokens/vehicle_token_factory.h"

namespace apperoso {

	inline constexpr auto carStyle = vehicleTokenFactory.create<CarPropertyEnum::style>();
	inline constexpr auto carDoorCount = vehicleTokenFactory.create<CarPropertyEnum::door_count>();
	inline constexpr auto carFuelType = vehicleTokenFactory.create<CarPropertyEnum::fuel_type>();

}