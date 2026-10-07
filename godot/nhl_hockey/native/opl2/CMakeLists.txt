# The port's native library (the OPL2 chip): a GDExtension against godot-cpp 4.3.
#   git clone --depth 1 --branch godot-4.3-stable https://github.com/godotengine/godot-cpp.git
#   cmake -S native/opl2 -B build-opl2 -DGODOT_CPP_DIR=/path/to/godot-cpp -DCMAKE_BUILD_TYPE=Release
#   cmake --build build-opl2 -j
# The library lands in native/bin (libopl2.<platform>.<arch>.so / .dll / .dylib, see opl2.gdextension).
cmake_minimum_required(VERSION 3.13)
project(opl2 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(GODOT_CPP_DIR "" CACHE PATH "godot-cpp checkout (godot-4.3-stable)")
if(NOT GODOT_CPP_DIR)
	message(FATAL_ERROR "set GODOT_CPP_DIR to a godot-cpp checkout")
endif()
add_subdirectory(${GODOT_CPP_DIR} godot-cpp EXCLUDE_FROM_ALL)

add_library(opl2 SHARED src/opl2_chip.cpp src/register_types.cpp)
target_link_libraries(opl2 PRIVATE godot-cpp)

if(WIN32)
	set(OPL2_PLATFORM windows)
elseif(APPLE)
	set(OPL2_PLATFORM macos)
else()
	set(OPL2_PLATFORM linux)
endif()
if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64|ARM64")
	set(OPL2_ARCH arm64)
else()
	set(OPL2_ARCH x86_64)
endif()
set_target_properties(opl2 PROPERTIES
	PREFIX "lib"
	OUTPUT_NAME "opl2.${OPL2_PLATFORM}.${OPL2_ARCH}"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bin"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bin")
if(NOT MSVC)
	target_link_options(opl2 PRIVATE -s)
endif()
