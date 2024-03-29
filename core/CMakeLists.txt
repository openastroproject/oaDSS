cmake_minimum_required(VERSION 3.10)

set ( CMAKE_CXX_STANDARD 20 )

set ( top ${CMAKE_SOURCE_DIR} )

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui LinguistTools)

add_compile_options ( -Wno-ignored-attributes )
add_compile_options ( -Wno-deprecated-enum-enum-conversion )
add_compile_options ( -march=haswell )
add_compile_options ( -O2 )
add_compile_options ( -fopenmp )

add_compile_definitions ( NDEBUG )

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB TS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/i18n/*.ts)

configure_file( i18n/translations_kernel.qrc translations_kernel.qrc COPYONLY)
qt5_add_translation(QM_FILES ${TS_FILES})
qt5_add_resources(I18N_QRCFILE ${CMAKE_CURRENT_BINARY_DIR}/translations_kernel.qrc)

add_library( dsscore
	AHDDemosaicing.cpp
	BackgroundCalibration.cpp
	Bayer.cpp
	BilinearParameters.cpp
	BitmapBase.cpp
	BitmapExt.cpp
	BitMapFiller.cpp
	BitmapInfo.cpp
	ChannelAlign.cpp
	ColorBitmap.cpp
	ColorHelpers.cpp
	ColorMultiBitmap.cpp
	CosmeticEngine.cpp
	DarkFrame.cpp
	DeBloom.cpp
	DeepStack.cpp
	DSSProgress.cpp
	EntropyInfo.cpp
	ExceptionHandling.cpp
	Filters.cpp
	FITSUtil.cpp
	FlatFrame.cpp
	FrameInfo.cpp
	FrameList.cpp
	GrayBitmap.cpp
	GreyMultiBitmap.cpp
	group.cpp
	ImageListModel.cpp
	imageloader.cpp
	MasterFrames.cpp
	MatchingStars.cpp
	MedianFilterEngine.cpp
	MemoryBitmap.cpp
	MultiBitmapProcess.cpp
	Multitask.cpp
	QEventLogger.cpp
	RAWUtils.cpp
	RegisterEngine.cpp
	RunningStackingEngine.cpp
	Settings.cpp
	SetUILanguage.cpp						# Very Windows-specific
	StackedBitmap.cpp
	StackingEngine.cpp
	StackingTasks.cpp
	StarMask.cpp
	TaskInfo.cpp
	TIFFUtil.cpp
	tracecontrol.cpp
	Workspace.cpp
	avx_avg.cpp
	avx_bitmap_filler.cpp
	avx_cfa.cpp
	avx.cpp
	avx_entropy.cpp
	avx_filter.cpp
	avx_histogram.cpp
	avx_luminance.cpp
	avx_output.cpp
	avx_support.cpp
	${I18N_QRCFILE}
)

target_include_directories ( dsscore
    PRIVATE
    ${top}/include
    ${top}/matrix
    ${top}/libzclass
    ${top}/libstackwalk
    ${top}/libdsscompat
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
)

set_property(TARGET dsscore PROPERTY POSITION_INDEPENDENT_CODE ON)
