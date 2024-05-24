cmake_minimum_required(VERSION 3.20.0)

project(incognito VERSION 0.1.0 LANGUAGES CXX)

# Project wide setup
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# Compiler-specific options
if (MSVC)
	# Set NOMINMAX to ensure Microsoft's min() & max() macros don't clash
	add_compile_definitions(NOMINMAX)

	# Turn on all warnings, warnings as errors but exclude external code
	# See https://github.com/cpp-best-practices/cppbestpractices/blob/master/02-Use_the_Tools_Available.md#user-content-msvc
	add_compile_options(/W4 /WX /external:anglebrackets /external:W0)

	# enable multi-processor compilation
	add_compile_options(/MP)
else()
	# lots of warnings and all warnings as errors
	add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()


# Add libraries, in dependency order
add_subdirectory(enum_utils)
add_subdirectory(property_utils)

# Add executables
add_subdirectory(vehicle_database)

# Set the startup project for Visual Studio
if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT vehicle_database)
endif()

