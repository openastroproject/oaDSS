cmake_minimum_required(VERSION 3.10)

set ( CMAKE_CXX_STANDARD 20 )

set( top ${CMAKE_SOURCE_DIR} )
set( cwd ${CMAKE_CURRENT_SOURCE_DIR} )

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Charts LinguistTools)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${cwd}/ui)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# otherwise the output from the SIMD stuff is messy
add_compile_options ( -Wno-ignored-attributes )
add_compile_options ( -march=haswell )
add_compile_options ( -O2 )

file(GLOB TS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/i18n/*.ts)

configure_file( i18n/translations.qrc translations.qrc COPYONLY)
qt5_add_translation(QM_FILES ${TS_FILES})
qt5_add_resources(I18N_QRCFILE ${CMAKE_CURRENT_BINARY_DIR}/translations.qrc)

add_executable ( dsslive
	ChartTab.cpp
	DeepSkyStackerLive.cpp
#	EmailSettings.cpp				# SMTP- and Windows-specific
	fileregistrar.cpp
	filestacker.cpp
	foldermonitor.cpp
	footprint.cpp
	imageviewer.cpp
	LiveSettings.cpp
	progresslive.cpp
	RestartMonitoring.cpp
	settingstab.cpp
	${I18N_QRCFILE}
	resources.qrc
)

target_include_directories ( dsslive
		PRIVATE
		${top}/include
		${Qt5Core_INCLUDE_DIRS}
		${Qt5Gui_INCLUDE_DIRS}
		${Qt5Widgets_INCLUDE_DIRS}
		${Qt5Charts_INCLUDE_DIRS}
		${top}/libtools
		${top}/libzclass
		${top}/libdsscompat
		${top}/core
		${cwd}
)

target_compile_options( dsslive PRIVATE -fPIC)

target_link_libraries( dsslive
	dsscore
	zclass
	Qt::Charts
	Qt::Widgets
	gomp
	exiv2
	cfitsio
	tiff
	raw
	z
	pthread
)
