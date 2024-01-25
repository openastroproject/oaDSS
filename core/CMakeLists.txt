cmake_minimum_required(VERSION 3.10)

set ( CMAKE_CXX_STANDARD 20 )

set ( top ${CMAKE_SOURCE_DIR} )

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

add_compile_options ( -Wno-ignored-attributes )
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
#	ChannelAlign.cpp						# BITMAP-related code
#	ColorBitmap.cpp							# BITMAP-related code
	ColorHelpers.cpp
#	ColorMultiBitmap.cpp				# default argument for template parameter
#	CosmeticEngine.cpp					# BITMAP-related code
#	DarkFrame.cpp								# BITMAP-related code
#	DeBloom.cpp									# BITMAP-related code
#	DeepStack.cpp								# Windows-specific code
	DSSProgress.cpp
	dss_settings.cpp
	EntropyInfo.cpp
	ExceptionHandling.cpp
#	File.cpp										# Windows-specific code
#	Filters.cpp									# BITMAP-specific code
#	FITSUtil.cpp								# Many compilation errors -- prototypes?
	FlatFrame.cpp
#	FrameInfo.cpp								# BITMAP-related code
	FrameList.cpp
	GrayBitmap.cpp
#	GreyMultiBitmap.cpp					# default argument for template parameter
	group.cpp
	ImageListModel.cpp
#	imageloader.cpp							# BITMAP-related code
#	MasterFrames.cpp						# BITMAP-related code
	MatchingStars.cpp
	MedianFilterEngine.cpp
	MemoryBitmap.cpp
	MultiBitmapProcess.cpp
	Multitask.cpp
	QEventLogger.cpp
#	RAWUtils.cpp								# pokes about in libRaw internals
#	RegisterEngine.cpp					# AVX, Windows-specific path handling
#	RunningStackingEngine.cpp		# BITMAP-related code
	Settings.cpp
	StackedBitmap.cpp
	StackingEngine.cpp
	StackingTasks.cpp
	StackWalker.cpp
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
