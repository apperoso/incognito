
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

#include <tuple>
#include <concepts>
#include <algorithm>

namespace apperoso {

	// ---------------------------------------------------------------------
	// Test if a tuple contains a particular type
	//
	// Implementation based on https://stackoverflow.com/a/63332387
	// 
	// Example:
	//	using numberTypes = std::tuple<int, float>;
	//	static_assert(tuple_contains_v<int, numberTypes>);
	//	static_assert(tuple_contains_v<char, numberTypes>);	// Fails
	//
	// ---------------------------------------------------------------------

	template<typename, typename>
	struct tuple_contains;

	template<typename T, typename... Ts>
	struct tuple_contains<T, std::tuple<Ts...>>
		: std::disjunction<std::is_same<Ts, T>...> {};

	template<typename... T>
	inline constexpr bool tuple_contains_v = tuple_contains<T...>::value;

	// ---------------------------------------------------------------------
	// Get the first index of the specified type in a tuple, or return 
	// tuple_size if the type is not found
	//
	// Implementation based on https://stackoverflow.com/a/64606884
	// 
	// Example:
	//	using myTypes = std::tuple<int, float, char, float>;
	//	static_assert(tuple_index_v<int, myTypes> == 0);
	//	static_assert(tuple_index_v<float, myTypes> == 1);
	//	static_assert(tuple_index_v<bool, myTypes> == 4);
	//
	// ---------------------------------------------------------------------

	template<typename T, typename Tuple>
	struct tuple_index;

	template<typename T, typename... Types>
	struct tuple_index<T, std::tuple<Types...>> {

		template<std::size_t... I>
		static constexpr std::size_t index(std::index_sequence<I...>) {
			return std::min({ (std::is_same_v<T, Types> ? I : sizeof...(Types))... });
		}

		static constexpr std::size_t value = index(std::index_sequence_for<Types...>{});
	};

	template<typename... T>
	inline constexpr std::size_t tuple_index_v = tuple_index<T...>::value;

	// ---------------------------------------------------------------------
	// Check if a type is a specialization of a template
	// 
	// Implementaion of is_specialization_of based on proposal 
	// https://wg21.link/P2098R0
	//
	// Example:
	//	template<typename T>
	//	struct Foo {};

	//	template<>
	//	struct Foo<int> {};

	//	template<typename T>
	//	using FooInstance = Foo<T>;

	//	struct BarInstance {};

	//	template<typename T>
	//	using is_foo_type = is_specialization_of<T, Foo>;

	//	template<typename T>
	//	inline constexpr bool is_foo_type_v = is_specialization_of_v<T, Foo>;

	//	template<typename T>
	//	concept FooType = is_foo_type_v<T>;

	//	void fooTest(FooType auto foo) {};

	//	int main() {
	//		fooTest(FooInstance<int>{});	// OK
	//		fooTest(BarInstance{});			// Fail - constraints not satisfied
	//	}
	// 
	// ---------------------------------------------------------------------

	template<typename T, template<typename...> typename Primary>
	struct is_specialization_of : std::false_type {};

	template<template<typename...> typename Primary, typename... Args>
	struct is_specialization_of<Primary<Args...>, Primary> : std::true_type {};

	template<typename T, template<typename...> typename Primary>
	inline constexpr bool is_specialization_of_v = is_specialization_of<T, Primary>::value;

}
