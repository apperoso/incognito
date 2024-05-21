
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

	inline constexpr auto name = vehicleTokenFactory.create<CommonPropertyEnum::name>();
	inline constexpr auto make = vehicleTokenFactory.create<CommonPropertyEnum::make>();
	inline constexpr auto model = vehicleTokenFactory.create<CommonPropertyEnum::model>();
	inline constexpr auto color = vehicleTokenFactory.create<CommonPropertyEnum::color>();

}