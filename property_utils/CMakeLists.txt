add_library(property_utils INTERFACE)

target_sources(property_utils INTERFACE
	"include/property_utils/property_token.h"
	"include/property_utils/property_traits.h"
)

target_include_directories(property_utils INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(property_utils INTERFACE enum_utils)

# Set the IDE structure to match the folder structure
get_target_property(sources property_utils SOURCES)

source_group(
	TREE ${CMAKE_CURRENT_SOURCE_DIR}
	FILES ${sources}
	)

# Set the startup project for Visual Studio
if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT property_utils)
endif()
