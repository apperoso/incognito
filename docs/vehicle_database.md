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

The `vehicleTokenFactory` is defined in vehicle_token_factory.h:

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

Each vehicle is defined by its own class, to allow them to all have separate implementations to suit their needs.

The only things they all have in common is the need to set and get properties. This is achieved via the vehicle property interface...

## VehiclePropertyInterface

This is a class template that stores the property values for a particular vehicle:

```cpp
template<SizedEnum SpecificPropertyEnumT>
class VehiclePropertyInterface {
    EnumValues<CommonPropertyEnum>    commonProperties_{};
    EnumValues<SpecificPropertyEnumT> specificProperties_{};
};
```

It provides an [EnumValues](enum_utils.md) object for the common properties and the vehicle-specific properties.

This interface should be specialised using the property enum for each vehicle type, e.g. `VehiclePropertyInterface<CarPropertyEnum>` for class `Car`.

The interface uses a type alias for the property token, defined in vehicle_definitions.h:

```cpp
using VehiclePropertyToken = PropertyToken<VehicleTypeEnum>;
```

Access to the properties is provided using get and set functions:

```cpp
PropertyStatus setProperty(this auto&& self, VehiclePropertyToken propertyToken, std::string_view value);
PropertyResult getProperty(this auto&& self, VehiclePropertyToken propertyToken);
```

The first parameter adds support for [CRTP](https://en.cppreference.com/w/cpp/language/crtp) using C++23's [deducing this](https://en.cppreference.com/w/cpp/language/function#explicit_object_parameter) feature.

`PropertyStatus` is an enum that provides the status of the set operation:

```cpp
enum class PropertyStatus { success, invalidProperty, invalidValue };
```

`PropertyResult` is a [std::expected](https://en.cppreference.com/w/cpp/utility/expected) variable that returns the requested property string if successful, or a `PropertyStatus` if the call fails.

The interface declares (but doesn't define) two validation functions:

```cpp
PropertyStatus validateCommonProperty(VehiclePropertyToken propertyToken, std::string_view value);
PropertyStatus validateSpecificProperty(VehiclePropertyToken propertyToken, std::string_view value);
```

These should be defined by the individual vehicle classes in order to validate the properties being set are correct, and have the correct values. If they return an error status, then the setProperty function won't update the stored value for that property.

## Car Class [VehiclePropertyInterface Example]

The car class publicly inherits from the VehiclePropertyInterface, passing its property enum as the template parameter:

```cpp
class Car : public VehiclePropertyInterface<CarPropertyEnum>
{
    friend class VehiclePropertyInterface;
    using VehiclePropertyInterface::VehiclePropertyInterface;

    PropertyStatus validateCommonProperty(VehiclePropertyToken propertyToken, std::string_view value);
    PropertyStatus validateSpecificProperty(VehiclePropertyToken propertyToken, std::string_view value);

    PropertyStatus validateDoorCount(std::string_view value);
};
```

Note: we have to declare VehiclePropertyInterface as a friend of this class to support CRTP.

In this example, we have added a validate function for the door count, to ensure it is either "3" or "5". This is called from the `validateSpecificProperty()` function.

## Vehicle Class

vehicle.h contains the definition of class Vehicle.

This class uses [type-erasure](https://www.youtube.com/watch?v=qn6OqefuH08) to store any vehicle class (Bicycle, Car, Plane, Truck) in the same object.

It provides `setProperty()` and `getProperty()` functions that call into the stored vehicle object.

It also implements a copy constructor, which is required for basic container support. The internal `clone()` function makes this functionality possible.

## Vehicle Factory Demo

Finally, there is a demo application showing how the property token may be used with the vehicle objects.

### vehicle_factory.h (& .cpp)

Defines a function to create a collection of each vehicle:

```cpp
using Bicycles = std::vector<Bicycle>;
using Cars = std::vector<Car>;
using Planes = std::vector<Plane>;
using Trucks = std::vector<Truck>;

Bicycles makeBicycles();
Cars makeCars();
Planes makePlanes();
Trucks makeTrucks();
```

The `make()` functions create a number of vehicles and set some of their properties.

Note that each [std::vector](https://en.cppreference.com/w/cpp/container/vector) holds a concrete vehicle type, and each `make()` function returns a *different* type...

### Demo.cpp

The main `Demo()` function creates a std::vector of class Vehicle objects, by calling `createVehicles()`

The import code from `createVehicles()` is:

```cpp
Vehicles vehicles;

vehicles.append_range(makeBicycles());
vehicles.append_range(makeCars());
vehicles.append_range(makePlanes());
vehicles.append_range(makeTrucks());
```

[append_range](https://en.cppreference.com/w/cpp/container/vector/append_range) is a C++23 feature to append one std::vector to another. In this code, four *different* types are appended to the same vehicles vector: this is achieved through the type-erasure described above.

The demo finishes by printing all of the properties of the vehicles stored in the std::vector.
