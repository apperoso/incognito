
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
#include <array>
#include <ranges>
#include <print>
#include <string>

namespace apperoso {

	// EnumValues is a wrapper around an array used to represent std::string entries for a EnumT
	// 
	// The array elements are accessed using the underlying enumeration, e.g. 
	//		EnumValues<CommonPropertyEnum> myValues;
	//		myValues[CommonPropertyEnum::left] = std::string{42};
	// 
	// Basic iterator support is also provided
	template<SizedEnum EnumT>
	class EnumValues {
	public:
		using EnumType = EnumT;
		using ArrayType = std::array<std::string, std::to_underlying(EnumT::enumSize)>;

	private:
		ArrayType values_;

	public:
		EnumValues(ArrayType values) : values_{ std::move(values) } {}
		EnumValues() : values_{} {}

		ArrayType::reference operator[](std::size_t index) { return values_[index]; }
		ArrayType::const_reference operator[](std::size_t index) const { return values_[index]; }
		ArrayType::reference operator[](EnumT index) { return values_[toIndex(index)]; }
		ArrayType::const_reference operator[](EnumT index) const { return values_[toIndex(index)]; }

		ArrayType::iterator begin() noexcept { return values_.begin(); }
		ArrayType::const_iterator begin() const noexcept { return values_.begin(); }
		ArrayType::iterator end() noexcept { return values_.end(); }
		ArrayType::const_iterator end() const noexcept { return values_.end(); }
	};

	template<SizedEnum EnumT>
	void printValues(EnumValues<EnumT> const& values) {
		for (auto const [index, value] : std::views::enumerate(values))
		{
			std::println("[{}] = [{}]", toString<EnumT>(index), value);
		}
	}

}
