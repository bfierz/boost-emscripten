cmake_minimum_required(VERSION 3.0)

# General project configurations
project(ConanBoost CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
	message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
	file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/develop/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
endif()
include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_run(
	REQUIRES
		boost/1.74.0
	PROFILE
		${CMAKE_SOURCE_DIR}/emc.profile
	BASIC_SETUP
	CMAKE_TARGETS
	BUILD
		missing
)

foreach(TGT ${CONAN_TARGETS})
	set_target_properties(${TGT}
		PROPERTIES
			MAP_IMPORTED_CONFIG_MINSIZEREL Release
			MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
	)
endforeach()

add_executable(conan_boost "")

set(SOURCE
	main.cpp
)
target_sources(conan_boost
	PRIVATE
		${SOURCE}
)
source_group("" FILES ${SOURCE})

target_link_libraries(conan_boost
	PRIVATE
		CONAN_PKG::boost
)
