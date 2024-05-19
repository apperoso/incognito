
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

	inline constexpr auto truckCapacity = vehicleTokenFactory.create<TruckPropertyEnum::capacity>();
	inline constexpr auto truckLength = vehicleTokenFactory.create<TruckPropertyEnum::length>();
	inline constexpr auto truckHeight = vehicleTokenFactory.create<TruckPropertyEnum::height>();
	inline constexpr auto truckLadenWeight = vehicleTokenFactory.create<TruckPropertyEnum::laden_weight>();
	inline constexpr auto trucktruckWheelCount = vehicleTokenFactory.create<TruckPropertyEnum::wheel_count>();

}