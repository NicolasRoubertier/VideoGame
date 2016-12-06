cmake_minimum_required(VERSION 2.6)
project(defend)

SET(SOURCES
	main.cpp
	enemy.cpp
	enemy.h
	tower.cpp
	tower.h
	grid.cpp
	grid.h
	mesh.cpp
	mesh.h
	shd.vp
	shd.fp
	shd.h
)

AUTO_BIND_SHADERS( shd )

ADD_EXECUTABLE(defend ${SOURCES})
TARGET_LINK_LIBRARIES(defend common ${LIBSL_LIBRARIES} ${LIBSL_GL_LIBRARIES})
