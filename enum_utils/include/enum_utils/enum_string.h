
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
#include <array>
#include <string_view>
#include <algorithm>

namespace apperoso {

	using namespace std::string_view_literals;

	// The EnumString is stored in an array, with the std::string_view referencing the FixedString data
	template<SizedEnum EnumT>
	using EnumStringArray = std::array<std::string_view, std::to_underlying(EnumT::enumSize)>;

	// Specialise enumStrings for each SizedEnum that you want to support
	template <SizedEnum EnumT>
	extern constexpr EnumStringArray<EnumT> enumStrings;
	
	template<SizedEnum EnumT>
	constexpr std::string_view toString(std::integral auto value) {
		if (value >= 0 && value < std::ssize(enumStrings<EnumT>)) {
			return enumStrings<EnumT>[value];
		}

		return "undefined"sv;
	}

	template<SizedEnum EnumT>
	constexpr std::string_view toString(EnumT entry) {
		return toString<EnumT>(std::to_underlying(entry));
	}

	template<SizedEnum EnumT>
	constexpr EnumT toEnum(std::string_view text) {

		if (auto it = std::ranges::find(enumStrings<EnumT>, text); it != enumStrings<EnumT>.end()) {
			return EnumT(std::distance(enumStrings<EnumT>.begin(), it));
		}

		return EnumT::enumSize;
	}

	// Prefix operator++ (to allow simple loops using enums)
	template<SizedEnum EnumT>
	EnumT& operator++(EnumT& e)
	{
		if (int val = std::to_underlying(e); 
			val >= 0 && val < std::to_underlying(EnumT::enumSize))
		{
			e = EnumT{ val+1 };
		}
		else
		{
			e = EnumT{ 0 };
		}

		return e;
	}

}
