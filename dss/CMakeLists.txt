cmake_minimum_required(VERSION 3.10)

set ( CMAKE_CXX_STANDARD 20 )

set( top ${CMAKE_SOURCE_DIR} )
set( cwd ${CMAKE_CURRENT_SOURCE_DIR} )

find_package(Qt5 REQUIRED COMPONENTS
		Core
		Widgets
		Gui
		Charts
		Network
		LinguistTools
		Help
)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${cwd}/ui)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# otherwise the output from the SIMD stuff is messy
add_compile_options ( -Wno-ignored-attributes )
add_compile_options ( -march=haswell )
add_compile_options ( -O2 )

add_compile_definitions ( NOGDIPLUS )

file(GLOB TS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/i18n/*.ts)

configure_file( i18n/translations.qrc translations.qrc COPYONLY)
qt5_add_translation(QM_FILES ${TS_FILES})
qt5_add_resources(I18N_QRCFILE ${CMAKE_CURRENT_BINARY_DIR}/translations.qrc)

add_executable ( DeepSkyStacker
	About.cpp
	AlignmentParameters.cpp
	AskRegistering.cpp
	BackgroundOptions.cpp
	BaseDialog.cpp
	BatchStacking.cpp
	CheckAbove.cpp
	CometStacking.cpp
	DeepSkyStacker.cpp
	DropFilesDlg.cpp
	editstars.cpp
	ExplorerBar.cpp
	ImageProperties.cpp
#	ImageSinks.cpp							# uses broken bits of libtools
	IntermediateFiles.cpp
	mrulist.cpp
	OutputTab.cpp
	picturelist.cpp
	PostCalibration.cpp
	ProcessingDlg.cpp						# David still working on this
	ProcessingSettings.cpp
	ProcessingSettingsDlg.cpp
	progressdlg.cpp
	RawDDPSettings.cpp
	RecommendedSettings.cpp
	RegisterSettings.cpp
	RenameGroup.cpp
	ResultParameters.cpp
	RGBTab.cpp
	SaveEditChanges.cpp
	SavePicture.cpp
	selectrect.cpp
	StackingDlg.cpp
	StackingParameters.cpp
	StackRecap.cpp
	StackSettings.cpp
	StarMaskDlg.cpp
	toolbar.cpp
	${I18N_QRCFILE}
	resources.qrc
)

target_include_directories ( DeepSkyStacker
		PRIVATE
		${top}/include
		${Qt5Charts_INCLUDE_DIRS}
		${Qt5Gui_INCLUDE_DIRS}
		${Qt5Widgets_INCLUDE_DIRS}
		${Qt5Network_INCLUDE_DIRS}
		${Qt5Core_INCLUDE_DIRS}
		${Qt5Help_INCLUDE_DIRS}
		${top}/libdelaunay
		${top}/libtools
		${top}/libzclass
		${top}/libdsscompat
		${top}/core
)

target_compile_options( DeepSkyStacker PRIVATE -fPIC)

target_link_libraries( DeepSkyStacker
  dsscore
  zclass
	delaunay
	dsstools
  Qt::Charts
  Qt::Gui
  Qt::Network
  Qt::Help
  Qt::Widgets
  Qt::Core
	gomp
	exiv2
  cfitsio
  tiff
	raw
  z
  pthread
)
