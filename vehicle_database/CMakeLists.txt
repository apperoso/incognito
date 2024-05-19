add_executable(vehicle_database)

target_sources(vehicle_database PUBLIC
	"include/vehicle_database/enums/bicycle_property_enum.h"
	"include/vehicle_database/enums/car_property_enum.h"
	"include/vehicle_database/enums/common_property_enum.h"
	"include/vehicle_database/enums/plane_property_enum.h"
	"include/vehicle_database/enums/truck_property_enum.h"
	"include/vehicle_database/enums/vehicle_type_enum.h"

	"include/vehicle_database/enum_strings/all_vehicle_enum_strings.h"
	"include/vehicle_database/enum_strings/bicycle_property_enum_string.h"
	"include/vehicle_database/enum_strings/car_property_enum_string.h"
	"include/vehicle_database/enum_strings/common_property_enum_string.h"
	"include/vehicle_database/enum_strings/plane_property_enum_string.h"
	"include/vehicle_database/enum_strings/truck_property_enum_string.h"
	"include/vehicle_database/enum_strings/vehicle_type_enum_string.h"

	"include/vehicle_database/tokens/bicycle_property_token.h"
	"include/vehicle_database/tokens/car_property_token.h"
	"include/vehicle_database/tokens/common_property_token.h"
	"include/vehicle_database/tokens/plane_property_token.h"
	"include/vehicle_database/tokens/truck_property_token.h"
	"include/vehicle_database/tokens/vehicle_token_factory.h"

	"src/vehicle_database/main.cpp"
)

target_include_directories(vehicle_database PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(vehicle_database PUBLIC property_utils enum_utils)

# Set the IDE structure to match the folder structure
get_target_property(sources vehicle_database SOURCES)

source_group(
	TREE ${CMAKE_CURRENT_SOURCE_DIR}
	FILES ${sources}
	)

# Set the startup project for Visual Studio
if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT vehicle_database)
endif()
