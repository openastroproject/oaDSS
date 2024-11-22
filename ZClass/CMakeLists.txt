set(PROJECT_NAME ZClass)
message("Configuring project: " ${PROJECT_NAME})
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

set(COMPILE_WARNING_AS_ERROR YES)

if ( ${QT_VERSION} VERSION_LESS 6.3.0)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
else()
qt_standard_project_setup()
endif()
set(CMAKE_AUTORCC ON)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "zdefs.h"
    "zexcbase.h"
    "zexcept.h"
    "zinttimr.h"
    "zmstrlck.h"
    "zptr.h"
    "zreslock.h"
    "zsingle.h"
    "ztrace.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "source/ZExcBase.cpp"
    "source/ZExcept.cpp"
    "source/zmstrlck.cpp"
    "source/zreslock.cpp"
    "source/ZTrace.cpp"
)
if(NOT WIN32)
set (Source_Files
    ${Source_Files}
    "source/zinttimr.cpp"
)
endif()

source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)

include(CheckIncludeFileCXX)
CHECK_INCLUDE_FILE_CXX(format HAVE_STD_FORMAT)
if ( HAVE_STD_FORMAT )
  add_compile_definitions( HAVE_STD_FORMAT )
else()
if ( BOOST_VERSION VERSION_GREATER_EQUAL 1.80.0 )
    add_compile_definitions( HAVE_BOOST_FORMAT )
else()
  message( "Neither std::format nor boost::format found")
endif()
endif()

################################################################################
# Target
################################################################################
if ( ${QT_VERSION} VERSION_LESS 6.2.0)
add_library(ZClass STATIC ${ALL_FILES})
else()
qt_add_library(ZClass STATIC ${ALL_FILES})
endif()

set_target_properties(ZClass PROPERTIES FOLDER "Libraries")
target_link_libraries(ZClass PRIVATE Qt::Core)

################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/./$ENV{PlatformTarget}/$<CONFIG>/"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/./$ENV{PlatformTarget}/$<CONFIG>/"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
)

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PRIVATE
    .
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
target_include_directories(${PROJECT_NAME} PRIVATE
	"$<$<CONFIG:Debug>:C:/Program Files (x86)/Visual Leak Detector/include>"
)
endif()

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Release>:"
        "NDEBUG"
    ">"
    "_LIB"
)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
target_compile_definitions(${PROJECT_NAME} PRIVATE
	WIN32
	_WINDOWS
	_SBCS
	)
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /RTC1
        >
        $<$<CONFIG:Release>:
            /GL-;
            /GF
        >
        /W3 /wd4996
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        /Zc:__cplusplus;
        /permissive-;
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
endif()

