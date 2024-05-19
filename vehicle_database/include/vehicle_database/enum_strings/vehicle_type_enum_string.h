
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

#include "vehicle_database/enums/vehicle_type_enum.h"
#include "enum_utils/enum_string.h"

namespace apperoso {

	template<>
	constexpr EnumStringArray<VehicleTypeEnum> enumStrings<VehicleTypeEnum> =
	{
		"common"sv,
		"bicycle"sv,
		"car"sv,
		"plane"sv,
		"truck"sv,
	};

}