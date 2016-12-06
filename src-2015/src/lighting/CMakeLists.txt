cmake_minimum_required(VERSION 2.6)
project(lighting)

SET(SOURCES
	main.cpp
	shd.vp
	shd.fp
	shd.h
)

AUTO_BIND_SHADERS( shd )

ADD_EXECUTABLE(lighting ${SOURCES})
TARGET_LINK_LIBRARIES(lighting common ${LIBSL_LIBRARIES} ${LIBSL_GL_LIBRARIES})
