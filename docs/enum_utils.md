# Enum Utils Design

The design of the PropertyToken makes heavy use of enumerations.

Enum Utils is a header-only library to support it.

It contains three files:

- enum_string.h
- enum_values.h
- sized_enum.h

## sized_enum.h

A "sized enum" has the following properties:

- Starts at 0
- Each member is one greater than the previous
- Final member is called `enumSize`

For example:

```cpp
enum class CommonPropertyEnum {
    name,
    make,
    model,
    color,

    enumSize
};
```

All of the enums used in Incognito are sized enums. A concept is used to help enforce this:

```cpp
template<typename EnumT>
concept SizedEnum = std::is_scoped_enum_v<EnumT> and requires(EnumT) {
    EnumT::enumSize;
};
```

This only provides basic protection, so care is still required!

Several helper functions are provided to work with sized enums:

```cpp
template<SizedEnum EnumT>
constexpr EnumT toEnum(std::integral auto value);

template<SizedEnum EnumT>
constexpr std::size_t toIndex(EnumT value)

template<SizedEnum EnumT>
EnumT& operator++(EnumT& e);

template<SizedEnum EnumT>
constexpr inline auto enumRange();
```

`toEnum()` and `toIndex()` provide conversion between integers and enum members

`operator++()` provides support for pre-incrementing a sized enum, for use in a simple for loop:

```cpp
for(auto entry = CommonPropertyEnum::name; entry < CommonPropertyEnum::enumSize; ++entry){
    std::println("Index [{}] = [{}]", toIndex(entry), toString(entry));
}
```

Output:

```
Index [0] = [name]
Index [1] = [make]
Index [2] = [model]
Index [3] = [color]
```

`enumRange()` provides support for a sized enum in a [range-based for loop](https://en.cppreference.com/w/cpp/language/range-for):

```cpp
for (auto const& entry : enumRange<CommonPropertyEnum>()) {
    std::println("Index [{}] = [{}]", toIndex(entry), toString(entry));
}
```

This gives the same output as the simple for loop:

```
Index [0] = [name]
Index [1] = [make]
Index [2] = [model]
Index [3] = [color]
```

Note: `toString()` is described in the enum_string.h section below.

## enum_string.h

Provides a constexpr container to hold the strings representing the members of a `SizedEnum`.

```cpp
template<SizedEnum EnumT>
using EnumStringArray = std::array<std::string_view, std::to_underlying(EnumT::enumSize)>;

template <SizedEnum EnumT>
extern constexpr EnumStringArray<EnumT> enumStrings;
```

In order to use an enum string, an implementation must provide a specialisation of enumStrings. Using `CommonPropertyEnum` as an example:

```cpp
template<>
constexpr EnumStringArray<CommonPropertyEnum> enumStrings<CommonPropertyEnum> =
{
    "name"sv,
    "make"sv,
    "model"sv,
    "color"sv,
;
```

Note: Care must be taken to ensure the strings match the enum members correctly. Compilation will fail if too many strings are defined, but **NOT** if too few are defined (the missing strings will be initialised as empty strings)

The following helper functions are provided for enum strings:

```cpp
template<SizedEnum EnumT>
constexpr std::string_view toString(std::integral auto value);

template<SizedEnum EnumT>
constexpr std::string_view toString(EnumT entry);

template<SizedEnum EnumT>
constexpr EnumT toEnum(std::string_view text);
```

The first overload of `toString()` will return the string corresponding to the member of `EnumT` at index `value`

The second overload of `toString()` will return the string corresponding to the enum member `entry`

`toEnum()` will return the member of `EnumT` that corresponds to the provided string (or `EnumT::enumSize` if no match found)

## enum_values.h

Defines the class EnumValues.

This is a wrapper class that provides storage for a single [std::string](https://en.cppreference.com/w/cpp/string/basic_string) for each member of a `SizedEnum`

The strings are stored in a [std::array](https://en.cppreference.com/w/cpp/container/array) of size `enumSize`

Member functions are provided to access the strings using operator[], either using an integer or an enum member, as well as iterators.

A helper function is also provided to print the contents of an EnumValues class:

```cpp
template<SizedEnum EnumT>
void printValues(EnumValues<EnumT> const& values);
```

