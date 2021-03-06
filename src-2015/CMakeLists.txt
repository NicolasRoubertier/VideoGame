cmake_minimum_required(VERSION 2.6)
project(gameprog)

OPTION(_GAMEPROG_BUILD_BOX2D   "Build Box2D" ON)
OPTION(_GAMEPROG_BUILD_BULLET  "Build Bullet" OFF)
OPTION(_GAMEPROG_BUILD_LUA     "Build LUA" ON)

OPTION(USE_LIBSL_BINARIES  "Use LibSL binaries from this package" ON)

OPTION(USE_SOUND "Use OpenAL and Libsndfile" ON)

IF (USE_LIBSL_BINARIES)
SET(LibSL_DIR        ${CMAKE_SOURCE_DIR}/../LibSL-bin-win32)
ENDIF (USE_LIBSL_BINARIES)

FIND_PACKAGE(LibSL)
INCLUDE_DIRECTORIES( ${LIBSL_INCLUDE_DIR} )
LINK_DIRECTORIES( ${LIBSL_BINARY_DIR} )
ADD_DEFINITIONS(-DUSE_GLUX)

INCLUDE_DIRECTORIES(common)
ADD_SUBDIRECTORY(common)

IF(WIN32)
ADD_DEFINITIONS(-DDATA_PATH=\"${CMAKE_SOURCE_DIR}/data/\")
ADD_DEFINITIONS(-DSRC_PATH=\"${CMAKE_SOURCE_DIR}/\")
ELSE(WIN32)
ADD_DEFINITIONS(-DDATA_PATH=\\"${CMAKE_SOURCE_DIR}/data/\\")
ADD_DEFINITIONS(-DSRC_PATH=\\"${CMAKE_SOURCE_DIR}/\\")
ENDIF(WIN32)

add_subdirectory( lib )
include_directories ( 
	${CMAKE_SOURCE_DIR}/lib/luabind
	${CMAKE_SOURCE_DIR}/lib/lua/src
	${CMAKE_SOURCE_DIR}/lib/boost
	${CMAKE_SOURCE_DIR}/lib/libsndfile/include
	${CMAKE_SOURCE_DIR}/lib/OpenAL/include
	${CMAKE_SOURCE_DIR}/lib/bullet/src
	${CMAKE_SOURCE_DIR}/lib
)
link_directories    ( ${CMAKE_SOURCE_DIR}/lib )
link_directories    ( ${CMAKE_SOURCE_DIR}/lib/OpenAL/libs/Win32)
link_directories    ( ${CMAKE_SOURCE_DIR}/lib/libsndfile/lib)

INCLUDE_DIRECTORIES( lib/Box2D/Box2D/ )
ADD_SUBDIRECTORY(src/spriteanim_with_box2d)
ADD_SUBDIRECTORY(src/Brothers)