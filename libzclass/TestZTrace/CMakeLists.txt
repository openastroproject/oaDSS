cmake_minimum_required(VERSION 3.10)

find_package ( Qt5 COMPONENTS Core )

add_executable ( TestZTrace
	TestZTrace.cpp
)

target_include_directories ( TestZTrace
    PRIVATE
    ..
)

target_compile_options( TestZTrace PRIVATE -fPIC )

target_link_directories ( TestZTrace
		PRIVATE ${CMAKE_SOURCE_DIR}/libzclass/source
)

target_link_libraries ( TestZTrace
		zclass
		Qt::Core
)
