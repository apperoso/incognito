
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

	public:
		VehiclePropertyInterface(std::string name) { commonProperties_[CommonPropertyEnum::name] = name; }
		constexpr std::string name(this auto&& self) { return self.commonProperties_[CommonPropertyEnum::name]; }

		PropertyStatus setProperty(this auto&& self, VehiclePropertyToken propertyToken, std::string_view value) {
			auto status = PropertyStatus::success;

			switch (propertyToken.keyType()) {
			case VehicleTypeEnum::common: 
				if (status = self.validateCommonProperty(propertyToken, value); status == PropertyStatus::success) {
					self.commonProperties_[propertyToken.propertyIndex()] = value;
					std::println("[{}] common property [{}] set to [{}]", self.name(), propertyToken.propertyName(), value);
				}
				else {
					std::println("[{}] ERROR - could not set common property [{}] to [{}]", self.name(), propertyToken.propertyName(), value);
				}
				break;

			case vehicleTokenFactory.keyFor<SpecificPropertyEnumT>():
				if (status = self.validateSpecificProperty(propertyToken, value); status == PropertyStatus::success) {
					self.specificProperties_[propertyToken.propertyIndex()] = value;
					std::println("[{}] specific property [{}] set to [{}]", self.name(), propertyToken.propertyName(), value);
				}
				else {
					std::println("[{}] ERROR - could not set specific property [{}] to [{}]", self.name(), propertyToken.propertyName(), value);
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

		VehiclePropertyStrings getPropertyStrings() const {
			VehiclePropertyStrings propertyStrings;
			propertyStrings.reserve(toIndex(CommonPropertyEnum::enumSize) + toIndex(SpecificPropertyEnumT::enumSize));

			for (auto const [index, entry] : std::views::enumerate(commonProperties_) ) {
				propertyStrings.emplace_back(toString<CommonPropertyEnum>(index), entry);
			}

			for (auto const [index, entry] : std::views::enumerate(specificProperties_)) {
				propertyStrings.emplace_back(toString<SpecificPropertyEnumT>(index), entry);
			}

			return propertyStrings;
		}
	};
}