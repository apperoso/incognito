
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
	constexpr EnumT toEnum(std::integral auto value) {
		if (value >= 0 && value < std::to_underlying(EnumT::enumSize)) {
			return static_cast<EnumT>(value);
		}

		return EnumT::enumSize;
	}

	template<SizedEnum EnumT>
	constexpr std::size_t toIndex(EnumT value) {
		return std::to_underlying(value);
	}

	// Prefix operator++ (to allow simple loops using enums)
	template<SizedEnum EnumT>
	EnumT& operator++(EnumT& e)
	{
		if (int val = std::to_underlying(e);
			val >= 0 && val < std::to_underlying(EnumT::enumSize))
		{
			e = EnumT{ val + 1 };
		}
		else
		{
			e = EnumT{ 0 };
		}

		return e;
	}

	// Range support...
	template<SizedEnum EnumT>
	constexpr inline auto enumRange() {
		return std::views::iota(0, std::to_underlying(EnumT::enumSize))
			| std::views::transform([](auto e) { return toEnum<EnumT>(e); });
	};
}
