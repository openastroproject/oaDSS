cmake_minimum_required(VERSION 3.10)

set ( CMAKE_CXX_STANDARD 20 )

set( top ${CMAKE_SOURCE_DIR} )
set( cwd ${CMAKE_CURRENT_SOURCE_DIR} )

find_package(Qt5 REQUIRED COMPONENTS Core Widgets )

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable ( dsscli
	progressconsole.cpp
	DeepSkyStackerCL.cpp
)

add_compile_definitions ( NOGDIPLUS )

target_include_directories ( dsscli
		PRIVATE
		${top}/include
		${Qt5Core_INCLUDE_DIRS}
		${Qt5Widgets_INCLUDE_DIRS}
		${top}/Tools
		${top}/libzclass
		${top}/core
)

target_compile_options( dsscli PRIVATE -fPIC)

target_link_libraries( dsscli
	dsscore
	zclass
	Qt::Widgets
	gomp
	exiv2
	cfitsio
	tiff
	raw
	z
	pthread
)
