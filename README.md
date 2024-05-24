# Incognito

Combining type erasure, CRTP, template metaprogramming and a sprinkling of C++23, to create an opaque token to access the properties of a collection of heterogeneous objects.

## Overview

This project was created whilst testing various designs for modelling the properties of a collection of user interface widgets.

It is not intended to be a production quality library that will support multiple environments: the code has been made available in the hope that the techniques may be useful in other projects.

The idea is to use a token to uniquely identify any property among a collection of objects. The token is then passed to a single API which can be used to read and write the properties of any object registered with the API.

The API is part of a type-erased class which encapsulates the objects, providing value semantics and allowing them all to be stored in the same container.

The idea is to use a token to uniquely identify any property among a collection of objects. The token is then passed to a single API which can be used to read and write the properties of any object registered with the API.

**Note**: This code has been tested on Windows 11 using Visual Studio 2022 version 17.9.2. It contains C++23 features which may not be fully supported on other compilers.

## Usage Example: Vehicle Database

The source code contains a demo project, vehicle database, to show how the property token is created and used.

This section provides a basic overview. For a more detailed analysis read the [design documenation](docs/README.md)

We start by defining four types of vehicle, each with its own set of properties:

|Bicycle|Car|Plane|Truck|
|:--|:--|:--|:--|
|style|style|engine count|capacity|
|gear count|door count|engine type|length|
|brake type|fuel type|passenger count|height|
|||range|laden weight|
||||wheel count|

There are also common properties that each vehicle type has: name, make, model, color

### Enumerations

We define scoped enums to represent the collection of vehicle types that we want to support, and all the properties:

```cpp
enum class VehicleTypeEnum     { common, bicycle, car, plane, truck, enumSize };
enum class CommonPropertyEnum  { name, make, model, color, enumSize };
enum class BicyclePropertyEnum { style,	gear_count, brake_type,	enumSize };
enum class CarPropertyEnum     { style,	door_count, fuel_type, enumSize };
enum class PlanePropertyEnum   { engine_count, engine_type, passenger_count, range, enumSize };
enum class TruckPropertyEnum   { capacity, length, height, laden_weight, wheel_count, enumSize };
```

Note:
- The VehicleTypeEnum will act as the key. We define "common" as a vehicle type so that it can be re-used for each vehicle. This is an implementation decision and doesn't need to be done this way!
- The design uses SizedEnums to keep track of how many enums we have defined. The always have "enumSize" as their last member. A C++20 concept ensures this member exists.

### Enum Strings

The design requires each enum member to have a string representation so that we can, for example, print the values of each property automatically.

The strings are implemented using enum strings

```cpp
template<> constexpr EnumStringArray<VehicleTypeEnum> enumStrings<VehicleTypeEnum> = { "common"sv, "bicycle"sv, "car"sv, "plane"sv, "truck"sv, };
template<> constexpr EnumStringArray<CommonPropertyEnum> enumStrings<CommonPropertyEnum> = { "name"sv, "make"sv, "model"sv, "color"sv, };
template<> constexpr EnumStringArray<BicyclePropertyEnum> enumStrings<BicyclePropertyEnum> = { "style"sv, "gear_count"sv, "brake_type"sv, };
template<> constexpr EnumStringArray<CarPropertyEnum> enumStrings<CarPropertyEnum> = { "style"sv, "door_count"sv, "fuel_type"sv, };
template<> constexpr EnumStringArray<PlanePropertyEnum> enumStrings<PlanePropertyEnum> = { "engine_count", "engine_type", "passenger_count", "range", };
template<> constexpr EnumStringArray<TruckPropertyEnum> enumStrings<TruckPropertyEnum> = { "capacity", "length", "height", "laden_weight", "wheel_count", };
```

Note: The enum strings can be automatically generated using [EnumString](https://github.com/apperoso/EnumString)

### Property Token Factory

We can now create the PropertyTokenFactory which maps the key (VehicleTypeEnum) to the properties represented by each member of the key. For example VehicleTypeEnum::car maps to CarPropertyEnum
The mapping is implied by the order that the enums are passed when creating the factory:

```cpp
inline constexpr auto vehicleTokenFactory = PropertyTokenFactory<
		VehicleTypeEnum,
		CommonPropertyEnum,
		BicyclePropertyEnum,
		CarPropertyEnum,
		PlanePropertyEnum,
		TruckPropertyEnum
	>{};
```

### Property Tokens

The property token factory is then used to define a unique property token for each property. A sample of tokens for the different vehicle types is shown below:

```cpp
inline constexpr auto name = vehicleTokenFactory.create<CommonPropertyEnum::name>();
inline constexpr auto bicycleStyle = vehicleTokenFactory.create<BicyclePropertyEnum::style>();
inline constexpr auto carStyle = vehicleTokenFactory.create<CarPropertyEnum::style>();
inline constexpr auto planeEngineCount = vehicleTokenFactory.create<PlanePropertyEnum::engine_count>();
inline constexpr auto truckCapacity = vehicleTokenFactory.create<TruckPropertyEnum::capacity>();
```

### Read/Write API

The property tokens can be used in an API as shown in the following example code:

```cpp
using VehiclePropertyToken = PropertyToken<VehicleTypeEnum>;

struct Car {
    void setProperty(VehiclePropertyToken propertyToken, std::string_view value);
    std::string getProperty(VehiclePropertyToken propertyToken);
};

Car car;
car.setProperty(carStyle, "hatchback");
```

## Design

For more detail on the design of Incognito, see the [design documenation](docs/README.md)
