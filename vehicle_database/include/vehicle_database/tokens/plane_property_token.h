
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

	inline constexpr auto planeEngineCount = vehicleTokenFactory.create<PlanePropertyEnum::engine_count>();
	inline constexpr auto planeEngineType = vehicleTokenFactory.create<PlanePropertyEnum::engine_type>();
	inline constexpr auto planePassengerCount = vehicleTokenFactory.create<PlanePropertyEnum::passenger_count>();
	inline constexpr auto planeRange = vehicleTokenFactory.create<PlanePropertyEnum::range>();

}