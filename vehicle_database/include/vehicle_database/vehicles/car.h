
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

#include "vehicle_database/vehicles/vehicle_property_interface.h"

namespace apperoso {

	class Car : public VehiclePropertyInterface<CarPropertyEnum>
	{
		friend class VehiclePropertyInterface;
		using VehiclePropertyInterface::VehiclePropertyInterface;

		PropertyStatus validateCommonProperty(VehiclePropertyToken propertyToken, std::string_view value);
		PropertyStatus validateSpecificProperty(VehiclePropertyToken propertyToken, std::string_view value);

		PropertyStatus validateDoorCount(std::string_view value);
	};
}