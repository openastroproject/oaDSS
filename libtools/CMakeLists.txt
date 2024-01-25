cmake_minimum_required(VERSION 3.10)

set( top ${CMAKE_SOURCE_DIR} )

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets )

add_library( dsstools
	imageview.cpp
	QElidedLabel.cpp
	QLinearGradientCtrl.cpp
#	BtnST.cpp
#	Bubble.cpp
#	ButtonToolbar.cpp
#	cdxCRot90DC.cpp
#	cdxCRotBevelLine.cpp
#	childprop.cpp
#	ControlPos.cpp
#	EditInterval.cpp
#	Gradient.cpp
#	GradientCtrl.cpp
#	GradientCtrlImpl.cpp
#	Label.cpp
#	MultiSlider.cpp
#	OXListBoxEx.cpp
#	WndImage.cpp
)

#target_compile_definitions ( dsstools PUBLIC ZCLASS_UNIX )

target_include_directories ( dsstools
    PRIVATE
		${top}/include
		${top}/libzclass
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
		${top}/junk
)

set_property(TARGET dsstools PROPERTY POSITION_INDEPENDENT_CODE ON)
