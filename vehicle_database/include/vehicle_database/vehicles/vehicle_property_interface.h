
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

#include "enum_utils/sized_enum.h"
#include "enum_utils/enum_values.h"
#include "vehicle_database/vehicles/vehicle_definitions.h"
#include "vehicle_database/enums/common_property_enum.h"
#include "vehicle_database/enums/vehicle_type_enum.h"
#include "vehicle_database/tokens/vehicle_token_factory.h"
#include <expected>
#include <string>

namespace apperoso {


	template<SizedEnum SpecificPropertyEnumT>
	class VehiclePropertyInterface {
		EnumValues<CommonPropertyEnum>		commonProperties_{};
		EnumValues<SpecificPropertyEnumT>	specificProperties_{};

		PropertyStatus validateCommonProperty(VehiclePropertyToken propertyToken, std::string_view value);
		PropertyStatus validateSpecificProperty(VehiclePropertyToken propertyToken, std::string_view value);

		static constexpr auto name_ = enumStrings<VehicleTypeEnum>[vehicleTokenFactory.keyIndexFor<SpecificPropertyEnumT>()];

	public:
		PropertyStatus setProperty(this auto&& self, VehiclePropertyToken propertyToken, std::string_view value) {
			auto status = PropertyStatus::success;

			switch (propertyToken.keyType()) {
			case VehicleTypeEnum::common: 
				if (status = self.validateCommonProperty(propertyToken, value); status == PropertyStatus::success) {
					self.commonProperties_[propertyToken.propertyIndex()] = value;
					std::println("[{}] common property [{}] set to [{}]", name_, propertyToken.propertyName(), value);
				}
				else {
					std::println("[{}] ERROR - could not set common property [{}] to [{}]", name_, propertyToken.propertyName(), value);
				}
				break;

			case vehicleTokenFactory.keyFor<SpecificPropertyEnumT>():
				if (status = self.validateSpecificProperty(propertyToken, value); status == PropertyStatus::success) {
					self.specificProperties_[propertyToken.propertyIndex()] = value;
					std::println("[{}] specific property [{}] set to [{}]", name_, propertyToken.propertyName(), value);
				}
				else {
					std::println("[{}] ERROR - could not set specific property [{}] to [{}]", name_, propertyToken.propertyName(), value);
				}
				break;
			}

			return status;
		}

		PropertyResult getProperty(this auto&& self, VehiclePropertyToken propertyToken) {
			switch (propertyToken.keyType()) {
			case VehicleTypeEnum::common:
				return self.commonProperties_[propertyToken.propertyIndex()];

			case vehicleTokenFactory.keyFor<SpecificPropertyEnumT>():
				return self.specificProperties_[propertyToken.propertyIndex()];
			}

			return std::unexpected(PropertyStatus::invalidProperty);
		}
	};
}