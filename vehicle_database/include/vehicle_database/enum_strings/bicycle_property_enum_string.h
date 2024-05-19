
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

#include "vehicle_database/enums/bicycle_property_enum.h"
#include "enum_utils/enum_string.h"

namespace apperoso {

	template<>
	constexpr EnumStringArray<BicyclePropertyEnum> enumStrings<BicyclePropertyEnum> =
	{
		"style"sv,
		"gear_count"sv,
		"brake_type"sv,
	};

}