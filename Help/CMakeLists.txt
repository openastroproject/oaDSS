cmake_minimum_required(VERSION 3.10)

set( top ${CMAKE_SOURCE_DIR} )
set( cwd ${CMAKE_CURRENT_SOURCE_DIR} )
set( bin ${CMAKE_CURRENT_BINARY_DIR} )

find_package(Qt5 REQUIRED COMPONENTS Help)

file(GLOB EN_DEPS
		english/*
		images/*.*
		images/Theory/*.*
		images/english/*.*
)

add_custom_command (
	OUTPUT dsshelp-en.qhc dsshelp-en.qch
	COMMAND qhelpgenerator ${cwd}/dsshelp-en.qhcp -s -o dsshelp-en.qhc
	COMMAND mv ${cwd}/dsshelp-en.qch ${bin}
	DEPENDS ${EN_DEPS}
	COMMENT "Generating English help files"
)

file(GLOB NL_DEPS
		dutch/*
		images/*.*
		images/Theory/*.*
		images/dutch/*.*
)

add_custom_command (
	OUTPUT dsshelp-nl.qhc dsshelp-nl.qch
	COMMAND qhelpgenerator ${cwd}/dsshelp-nl.qhcp -s -o dsshelp-nl.qhc
	COMMAND mv ${cwd}/dsshelp-nl.qch ${bin}
	DEPENDS ${NL_DEPS}
	COMMENT "Generating Dutch help files"
)

file(GLOB DE_DEPS
		german/*
		images/*.*
		images/Theory/*.*
		images/german/*.*
)

add_custom_command (
	OUTPUT dsshelp-de.qhc dsshelp-de.qch
	COMMAND qhelpgenerator ${cwd}/dsshelp-de.qhcp -s -o dsshelp-de.qhc
	COMMAND mv ${cwd}/dsshelp-de.qch ${bin}
	DEPENDS ${DE_DEPS}
	COMMENT "Generating German help files"
)

file(GLOB FR_DEPS
		french/*
		images/*.*
		images/Theory/*.*
		images/french/*.*
)

add_custom_command (
	OUTPUT dsshelp-fr.qhc dsshelp-fr.qch
	COMMAND qhelpgenerator ${cwd}/dsshelp-fr.qhcp -s -o dsshelp-fr.qhc
	COMMAND mv ${cwd}/dsshelp-fr.qch ${bin}
	DEPENDS ${FR_DEPS}
	COMMENT "Generating French help files"
)

file(GLOB ES_DEPS
		spanish/*
		images/*.*
		images/Theory/*.*
		images/spanish/*.*
)

add_custom_command (
	OUTPUT dsshelp-es.qhc dsshelp-es.qch
	COMMAND qhelpgenerator ${cwd}/dsshelp-es.qhcp -s -o dsshelp-es.qhc
	COMMAND mv ${cwd}/dsshelp-es.qch ${bin}
	DEPENDS ${ES_DEPS}
	COMMENT "Generating Spanish help files"
)

file(GLOB PT_DEPS
		portuguese/*
		images/*.*
		images/Theory/*.*
		images/portuguese/*.*
)

add_custom_command (
	OUTPUT dsshelp-pt.qhc dsshelp-pt.qch
	COMMAND qhelpgenerator ${cwd}/dsshelp-pt.qhcp -s -o dsshelp-pt.qhc
	COMMAND mv ${cwd}/dsshelp-pt.qch ${bin}
	DEPENDS ${PT_DEPS}
	COMMENT "Generating Portuguese help files"
)

add_custom_target ( helpfiles ALL DEPENDS
	dsshelp-en.qhc
	dsshelp-nl.qhc
	dsshelp-de.qhc
	dsshelp-fr.qhc
	dsshelp-es.qhc
	dsshelp-pt.qhc
)
