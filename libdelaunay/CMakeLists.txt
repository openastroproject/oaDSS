cmake_minimum_required(VERSION 3.10)

set ( CMAKE_CXX_STANDARD 20 )

set( top ${CMAKE_SOURCE_DIR} )

find_package(Qt5 REQUIRED COMPONENTS Core Widgets )

add_compile_options ( -Wno-ignored-attributes )
add_compile_options ( -Wno-deprecated-enum-enum-conversion )
add_compile_options ( -march=haswell )
add_compile_options ( -O2 )

add_library( delaunay
	Delaunay.cpp
)

target_include_directories ( delaunay
    PRIVATE
		${top}/include
		${top}/libzclass
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
)

set_property(TARGET delaunay PROPERTY POSITION_INDEPENDENT_CODE ON)
