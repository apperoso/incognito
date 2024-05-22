# Property Utils Design

This is a header-only library, comprising two files:

- property_token.h
- property_traits.h

## property_token.h

This header contains all of the definitions required to create a PropertyToken object.

It uses template metaprogramming and constexpr functions to allow the property tokens to be created from compile-time definitions, and hence used directly in the demo source code.

### PropertyTokenFactory

This is the entry point. It's declaration is:

```cpp
template<SizedEnum KeyEnumT, SizedEnum... PropertyEnumTs>
    requires (std::to_underlying(KeyEnumT::enumSize) == sizeof...(PropertyEnumTs))
struct PropertyTokenFactory;
```

The template parameters define the enums used to create the final property tokens.
- `KeyEnumT` is the enum that defines all of the object types. This becomes the key enum. 
- `PropertyEnumTs` are all of the enums defining the properties that correspond to the entries in the key enum.

In the demo, the key enum is `VehicleTypeEnum`, which results in the creation of `PropertyToken<VehicleTypeEnum>` objects.

`SizedEnum` is a concept that ensures the enum has a member called enumSize, which is used to determine how many entries the enum contains. See [enum_utils](enum_utils.md) for more information.

The requires clause ensures that there is one property enum supplied for every entry in ther key enum.

Upon instantiation, the struct stores the type KeyEnumT as `KeyType`, and the types of PropertyEnumTs in the [std::tuple](https://en.cppreference.com/w/cpp/utility/tuple) `PropertyTypes`.

Two helper functions are provided by the factory class: keyIndexFor() and keyFor()

```cpp
template<SizedEnum PropertyEnumT>
    requires (tuple_contains_v<PropertyEnumT, PropertyTypes>)
static constexpr std::size_t keyIndexFor();

template<SizedEnum PropertyEnumT>
    requires (tuple_contains_v<PropertyEnumT, PropertyTypes>)
static constexpr KeyType keyFor();
```

`keyIndexFor()` uses the property trait `tuple_index_v` (see below) to search the `PropertyTypes` tuple for the enum type requested in the template parameter `PropertyEnumT`.
Its index in the tuple is then returned.
The requires clause uses the property trait `tuple_contains_v` (see below) to ensure `PropertyEnumT` is in `PropertyTypes`, thus ensuring a valid index is always returned.

`keyFor()` takes the index returned from `keyIndexFor()` and returns the member at that index in the enum defined by `KeyType`
It therefore provides a mapping from a property enum back to the corresponding key enum entry.
The same requires clause is used as with `keyIndexFor()`

The property token is created by calling the create() function:

```cpp
template<SizedEnum auto propertyEnum>
    requires (tuple_contains_v<decltype(propertyEnum), PropertyTypes>)
constexpr auto create() const noexcept;
```

`create()` is called by passing a [non-type template parameter](https://en.cppreference.com/w/cpp/language/template_parameters), `propertyEnum`, representing the property that the token will represent (for example, `CarPropertyEnum::fuel_type`).

`keyFor()` is called with the type of `propertyEnum` to determine which key type to use. For example the key type for `CarPropertyEnum::fuel_type` is `VehicleTypeEnum::car` in the demo.

These values are then used to instantiate `PropertyTokenDataFactory` and return the PropertyToken obtained from its `create()` function (below).

### PropertyTokenDataFactory

This is a helper object. Its full declaration is:

```cpp
template<SizedEnum KeyEnumT, KeyEnumT keyType, SizedEnum auto propertyEnum>
struct PropertyTokenDataFactory {
    static constexpr auto name_ = enumStrings<decltype(propertyEnum)>[std::to_underlying(propertyEnum)];
    static constexpr auto data_ = PropertyTokenData<KeyEnumT>{keyType, std::to_underlying(propertyEnum), name_};
    constexpr auto create() const noexcept { return PropertyToken<KeyEnumT>{ &data_ }; }
};
```

Its job is to create static storage for the data that the property token uses, to ensure it is available for the lifetime of the application.

When instantiated, two static members are created: name_ and data_
- name_ is the textual representation of `propertyEnum`, referenced in the [enumStrings](enum_utils.md) array. For example, `"fuel_type"sv` for `CarPropertyEnum::fuel_type`
- data_ is a `PropertyTokenData` instance (see below) built from the key enum type, `propertyEnum` and `name_`

This means that there is a `name_` and `data_` static instance for each `keyType, propertyEnum` pair. 
For example: `PropertyTokenDataFactory<VehicleTypeEnum, VehicleTypeEnum::car, CarPropertyEnum::fuel_type>` pairs `VehicleTypeEnum::car, CarPropertyEnum::fuel_type`

Finally, the `create()` function creates the PropertyToken from the `data_` instance and returns this back to `PropertyTokenFactory::create()`

### PropertyTokenData

The `PropertyTokenData` object holds the data used by the `PropertyToken`:

```cpp
template<SizedEnum KeyEnumT>
struct PropertyTokenData {
    KeyEnumT keyType_;
    int propertyIndex_;
    std::string_view propertyName_;
};
```

Where:
- `keyType_` is the enum for this type of PropertyToken, for example `VehicleTypeEnum::car` for `PropertyTokenData<VehicleTypeEnum>`
- `propertyIndex_` is the underlying integer value for the `propertyEnum` used to create the data. For example `2` for `CarPropertyEnum::fuel_type`
- `propertyName_` refers to the `name_` static instance in the PropertyTokenDataFactory

`propertyIndex_` provides the type erasure that allows this design to work. With it, we can store the value of multiple property enums using the same data type. For example:

```cpp
// Here, name_ is a string_view as described above
PropertyTokenData<VehicleTypeEnum>{VehicleTypeEnum::bicycle, 0, name_}; // Index 0 is BicyclePropertyEnum::style
PropertyTokenData<VehicleTypeEnum>{VehicleTypeEnum::car,     2, name_}; // Index 2 is CarPropertyEnum::fuel_type
PropertyTokenData<VehicleTypeEnum>{VehicleTypeEnum::plane,   3, name_}; // Index 3 is PlanePropertyEnum::range
PropertyTokenData<VehicleTypeEnum>{VehicleTypeEnum::truck,   4, name_}; // Index 4 is TruckPropertyEnum::wheel_count
```

Using a single `PropertyTokenData<VehicleTypeEnum>` type, we can represent all properties for bicycles, cars, planes and trucks and therefore only need a single function to set and get them all. This is shown in the Vehicle Database demo.

### PropertyToken

The PropertyToken object is just a wrapper that holds a pointer to the PropertyTokenData:

```cpp
template<SizedEnum KeyEnumT>
class PropertyToken {
    PropertyTokenData<KeyEnumT> const* data_;
    /* ... */
};
```

This keeps it very lightweight and means it can be passed to functions by value.

The constructor is private, and can only be accessed by the `PropertyTokenDataFactory`. This ensures it is constructed correctly and ensures only one PropertyToken object exists per object property.

Public member functions are provided to access the underlying data:

- `keyType()` returns the key type as an enum, e.g. `VehicleTypeEnum::plane`
- `keyName()` returns the key type as a string_view, e.g. `"plane"sv`
- `propertyIndex()` returns the `propertyEnum` index, e.g. `3` for `PlanePropertyEnum::range`
- `propertyName()` returns the `propertyEnum` as a string_view, e.g. `"range"sv` for `PlanePropertyEnum::range`


## property_traits.h

This header provides some utilities used by property_token.h

### tuple_contains

Use this to determine if a [std::tuple](https://en.cppreference.com/w/cpp/utility/tuple) holds a particular type:

```cpp
using numberTypes = std::tuple<int, float>;

static_assert(tuple_contains_v<int, numberTypes>);
static_assert(tuple_contains_v<char, numberTypes>);	// Fails
```

The implementation is based on [this](https://stackoverflow.com/a/63332387)

### tuple_index

If a [std::tuple](https://en.cppreference.com/w/cpp/utility/tuple) holds a particular type, then it returns the index of the *first instance* of that type.

If the tuple doesn't hold the type, it returns the size of the tuple (i.e. the index is equivalent to `end`)

```cpp
using myTypes = std::tuple<int, float, char, float>;

static_assert(tuple_index_v<int, myTypes> == 0);
static_assert(tuple_index_v<float, myTypes> == 1);
static_assert(tuple_index_v<bool, myTypes> == 4);
```

The implementation is based on [this](https://stackoverflow.com/a/64606884)

### is_specialization_of

Check if a type is a specialization of a template.

```cpp
template<typename T>
struct Foo {};

template<>
struct Foo<int> {};

template<typename T>
using FooInstance = Foo<T>;

struct BarInstance {};

template<typename T>
using is_foo_type = is_specialization_of<T, Foo>;

template<typename T>
inline constexpr bool is_foo_type_v = is_specialization_of_v<T, Foo>;

template<typename T>
concept FooType = is_foo_type_v<T>;

void fooTest(FooType auto foo) {};

int main() {
	fooTest(FooInstance<int>{});	// OK
	fooTest(BarInstance{});			// Fail - constraints not satisfied
}
```

The implementation is based on proposal [P2098R0](https://wg21.link/P2098R0)
