cmake_minimum_required(VERSION 3.10)

set ( CMAKE_CXX_STANDARD 20 )

set ( top ${CMAKE_SOURCE_DIR} )

add_compile_options ( -Wno-ignored-attributes )
add_compile_options ( -Wno-deprecated-enum-enum-conversion )
add_compile_options ( -march=haswell )
add_compile_options ( -O2 )

add_library( stackwalk
	StackWalker.cpp
)

target_include_directories ( dsscore
    PRIVATE
    ${top}/include
)

set_property(TARGET dsscore PROPERTY POSITION_INDEPENDENT_CODE ON)
