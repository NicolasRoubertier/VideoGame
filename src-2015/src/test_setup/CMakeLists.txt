cmake_minimum_required(VERSION 2.6)
project(view3d)

SET(SOURCES
	main.cpp
	shd.vp
	shd.fp
	shd.h
)

AUTO_BIND_SHADERS( shd )

ADD_EXECUTABLE(view3d ${SOURCES})
TARGET_LINK_LIBRARIES(view3d common ${LIBSL_LIBRARIES} ${LIBSL_GL_LIBRARIES})
