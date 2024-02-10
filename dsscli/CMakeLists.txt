cmake_minimum_required(VERSION 3.10)

set ( CMAKE_CXX_STANDARD 20 )

set( top ${CMAKE_SOURCE_DIR} )
set( cwd ${CMAKE_CURRENT_SOURCE_DIR} )

find_package(Qt5 REQUIRED COMPONENTS Core Widgets LinguistTools)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_compile_definitions ( NOGDIPLUS )

file(GLOB TS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/i18n/*.ts)

configure_file( i18n/translations.qrc translations.qrc COPYONLY)
qt5_add_translation(QM_FILES ${TS_FILES})
qt5_add_resources(I18N_QRCFILE ${CMAKE_CURRENT_BINARY_DIR}/translations.qrc)

add_executable ( dsscli
	progressconsole.cpp
	DeepSkyStackerCL.cpp
	${I18N_QRCFILE}
)

target_include_directories ( dsscli
		PRIVATE
		${top}/include
		${Qt5Core_INCLUDE_DIRS}
		${Qt5Widgets_INCLUDE_DIRS}
		${top}/Tools
		${top}/libzclass
		${top}/core
		${top}/libdsscompat
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
