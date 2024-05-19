
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

#include <utility>
#include <concepts>
#include <ranges>

namespace apperoso {

	// The SizedEnum concept is used to ensure the enum has an "enumSize" member
	template<typename EnumT>
	concept SizedEnum = std::is_scoped_enum_v<EnumT> and requires(EnumT) {
		EnumT::enumSize;
	};

	template<SizedEnum EnumT>
	constexpr EnumT toSizedEnum(int value) {
		if (value >= 0 && value < std::to_underlying(EnumT::enumSize)) {
			return static_cast<EnumT>(value);
		}

		return static_cast<EnumT>(EnumT::enumSize);
	}

	// Range support...
	template<SizedEnum EnumT>
	constexpr inline auto enumRange() {
		return std::views::iota(0, std::to_underlying(EnumT::enumSize))
			| std::views::transform([](auto e) { return static_cast<EnumT>(e); });
	};
}
