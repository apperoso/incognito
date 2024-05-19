
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
#include "vehicle_database/tokens/vehicle_token_factory.h"
#include <expected>
#include <string>

namespace apperoso {

	enum class PropertyStatus {
		success,
		invalidProperty,
		invalidValue
	};

	using PropertyResult = std::expected<std::string, PropertyStatus>;

	using VehiclePropertyToken = PropertyToken<VehicleTypeEnum>;

}