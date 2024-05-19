
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

#include <algorithm>
#include <string_view>

// Provides a (basic) compile-time fixed string with no allocations, that can be used as a non-type template parameter

namespace apperoso {
    template <auto Size>
    struct FixedString {
        char data[Size + 1]{};
        static constexpr auto size = Size;

        constexpr explicit(false) FixedString(char const* str) {
            std::copy_n(str, Size + 1, data);
        }

        constexpr explicit(false) operator std::string_view() const {
            return { data, Size };
        }
    };

    // Deduction guide to get size from string literal
    // Note we use std::size_t instead of auto otherwise Visual Studio intellisense complains (although it compiles correctly!)
    template <std::size_t Size>
    FixedString(char const (&)[Size]) -> FixedString<Size - 1>;

    using std::literals::string_view_literals::operator""sv;

    static_assert(""sv == FixedString(""));
    static_assert("name"sv == FixedString("name"));
}
