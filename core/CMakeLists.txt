cmake_minimum_required(VERSION 3.10)

set ( CMAKE_CXX_STANDARD 20 )

set ( top ${CMAKE_SOURCE_DIR} )

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

add_compile_options ( -Wno-ignored-attributes )
add_compile_options ( -Wno-deprecated-enum-enum-conversion )
add_compile_options ( -march=haswell )
add_compile_options ( -O2 )

add_library( dsscore
	AHDDemosaicing.cpp
	BackgroundCalibration.cpp
	Bayer.cpp
	BilinearParameters.cpp
	BitmapBase.cpp
#	BitmapExt.cpp								# Still has Windows-specific code
	BitMapFiller.cpp
	BitmapInfo.cpp
	ChannelAlign.cpp
	ColorBitmap.cpp
	ColorHelpers.cpp
#	ColorMultiBitmap.cpp				# default argument for template parameter
	CosmeticEngine.cpp
	DarkFrame.cpp
	DeBloom.cpp
	DeepStack.cpp
	DSSProgress.cpp
	dss_settings.cpp
	EntropyInfo.cpp
	ExceptionHandling.cpp
#	File.cpp										# Windows-specific code
	Filters.cpp
	FITSUtil.cpp
	FlatFrame.cpp
	FrameInfo.cpp
	FrameList.cpp
	GrayBitmap.cpp
#	GreyMultiBitmap.cpp					# default argument for template parameter
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
#	RAWUtils.cpp								# pokes about in libRaw internals
#	RegisterEngine.cpp					# AVX, Windows-specific path handling
	RunningStackingEngine.cpp
	Settings.cpp
	StackedBitmap.cpp
	StackingEngine.cpp
	StackingTasks.cpp
#	StackWalker.cpp							# Platform not supported!
	StarMask.cpp
	TaskInfo.cpp
	TIFFUtil.cpp
	tracecontrol.cpp
#	Workspace.cpp								# Qt6 specifics
#	avx_avg.cpp									# AVX
	avx_bitmap_filler.cpp
	avx_cfa.cpp
#	avx.cpp											# AVX
#	avx_entropy.cpp							# AVX
#	avx_filter.cpp							# AVX
	avx_histogram.cpp
	avx_luminance.cpp						# AVX
#	avx_output.cpp							# AVX (var.m256_f32[n])
#	avx_support.cpp							# AVX
)

target_include_directories ( dsscore
    PRIVATE
    ${top}/include
    ${top}/matrix
    ${top}/libzclass
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
)

set_property(TARGET dsscore PROPERTY POSITION_INDEPENDENT_CODE ON)
