cmake_minimum_required(VERSION 3.10)

find_package(Qt5 REQUIRED COMPONENTS Core )

add_library( zclass
	ZExcBase.cpp
	ZExcept.cpp
	zinttimr.cpp
	zmstrlck.cpp
	zreslock.cpp
	ZTrace.cpp
)

target_compile_definitions ( zclass PUBLIC ZCLASS_UNIX )

target_include_directories ( zclass
    PRIVATE
    ..
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
)

set_property(TARGET zclass PROPERTY POSITION_INDEPENDENT_CODE ON)
