# Vehicle Database Design

This is a demo of how to use the property token with a type-erased wrapper to provide a simple interface for reading and writing the properties of different types of vehicle.

There are four types of vehicle, each with its own set of properties:

|Bicycle|Car|Plane|Truck|
|:--|:--|:--|:--|
|style|style|engine count|capacity|
|gear count|door count|engine type|length|
|brake type|fuel type|passenger count|height|
|||range|laden weight|
||||wheel count|

There are also common properties that each vehicle type has: name, make, model, color

Each vehicle is represented by its own class. 

The interface to set/get the properties is created using the [CRTP](https://en.cppreference.com/w/cpp/language/crtp) pattern (updated to use C++23's [deducing this](https://en.cppreference.com/w/cpp/language/function#explicit_object_parameter)), rather than a class hierarchy.

A [type-erased](https://www.youtube.com/watch?v=qn6OqefuH08) Vehicle class is used to hold each of the four vehicle types, allowing them to all be stored in the same container using [value semantics](https://www.youtube.com/watch?v=G9MxNwUoSt0).

# Definition Files

The definitions are defined in header files split into several sections...

## enums

All of the `SizedEnum` definitions are here. In summary:

```cpp
enum class VehicleTypeEnum     { common, bicycle, car, plane, truck, enumSize };
enum class CommonPropertyEnum  { name, make, model, color, enumSize };
enum class BicyclePropertyEnum { style,	gear_count, brake_type,	enumSize };
enum class CarPropertyEnum     { style,	door_count, fuel_type, enumSize };
enum class PlanePropertyEnum   { engine_count, engine_type, passenger_count, range, enumSize };
enum class TruckPropertyEnum   { capacity, length, height, laden_weight, wheel_count, enumSize };
```

## enum_strings

Each enum has a corresponding enumString, for example:

```cpp
template<>
constexpr EnumStringArray<BicyclePropertyEnum> enumStrings<BicyclePropertyEnum> = {
    "style"sv,
    "gear_count"sv,
    "brake_type"sv,
};
```

## tokens

The enums and enumStrings are then used to define the property tokens. Continuing the Bicycle example:

```cpp
inline constexpr auto bicycleStyle = vehicleTokenFactory.create<BicyclePropertyEnum::style>();
inline constexpr auto bicycleGearCount = vehicleTokenFactory.create<BicyclePropertyEnum::gear_count>();
inline constexpr auto bicycleBrakeType = vehicleTokenFactory.create<BicyclePropertyEnum::brake_type>();
```

The vehicleTokenFactory is defined in vehicle_token_factory.h:

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

# Vehicles

TODO
