add_library(enum_utils INTERFACE)

target_sources(enum_utils INTERFACE
	"include/enum_utils/enum_string.h"
	"include/enum_utils/enum_values.h"
	"include/enum_utils/sized_enum.h"
)

target_include_directories(enum_utils INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Set the IDE structure to match the folder structure
get_target_property(sources enum_utils SOURCES)

source_group(
	TREE ${CMAKE_CURRENT_SOURCE_DIR}
	FILES ${sources}
	)

# Set the startup project for Visual Studio
if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT enum_utils)
endif()
