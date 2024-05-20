
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
#include "enum_utils/enum_string.h"
#include "property_utils/property_traits.h"
#include <string_view>

namespace apperoso {

	template<SizedEnum KeyEnumT>
	struct PropertyTokenData {
		KeyEnumT keyType_;
		int propertyIndex_;
		std::string_view propertyName_;
	};

	template<SizedEnum KeyEnumT>
	class PropertyToken {
		PropertyTokenData<KeyEnumT> const* data_;
		constexpr explicit PropertyToken(PropertyTokenData<KeyEnumT> const* data) noexcept : data_{ data } {}

		template<SizedEnum KeyEnumT, KeyEnumT keyType, SizedEnum auto propertyEnum>
		friend struct PropertyTokenDataFactory;

	public:
		constexpr KeyEnumT keyType() const noexcept { return data_->keyType_; }
		constexpr std::string_view keyName() const noexcept { return enumStrings<KeyEnumT>[std::to_underlying(keyType())]; }
		constexpr int propertyIndex() const noexcept { return data_->propertyIndex_; }
		constexpr std::string_view propertyName() const noexcept { return data_->propertyName_; }
	};

	template<SizedEnum KeyEnumT, KeyEnumT keyType, SizedEnum auto propertyEnum>
	struct PropertyTokenDataFactory {
		static constexpr auto name_ = enumStrings<decltype(propertyEnum)>[std::to_underlying(propertyEnum)];
		static constexpr auto data_ = PropertyTokenData<KeyEnumT>{keyType, std::to_underlying(propertyEnum), name_};
		constexpr auto create() const noexcept { return PropertyToken<KeyEnumT>{ &data_ }; }
	};

	template<SizedEnum KeyEnumT, SizedEnum... PropertyEnumTs>
		requires (std::to_underlying(KeyEnumT::enumSize) == sizeof...(PropertyEnumTs))
	struct PropertyTokenFactory {
		using KeyType = KeyEnumT;
		using PropertyTypes = std::tuple<PropertyEnumTs...>;

		template<SizedEnum PropertyEnumT>
			requires (tuple_contains_v<PropertyEnumT, PropertyTypes>)
		static constexpr std::size_t keyIndexFor() {
			return tuple_index_v<PropertyEnumT, PropertyTypes>;
		}

		template<SizedEnum PropertyEnumT>
			requires (tuple_contains_v<PropertyEnumT, PropertyTypes>)
		static constexpr KeyType keyFor() {
			return toEnum<KeyType>(keyIndexFor<PropertyEnumT>());
		}

		template<SizedEnum auto propertyEnum>
			requires (tuple_contains_v<decltype(propertyEnum), PropertyTypes>)
		constexpr auto create() const noexcept {
			return PropertyTokenDataFactory<KeyEnumT, keyFor<decltype(propertyEnum)>(), propertyEnum>{}.create();
		} 
	};

}
