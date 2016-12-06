cmake_minimum_required(VERSION 2.6)
project(bullet)

SET(SOURCES
	main.cpp
	shd.vp
	shd.fp
	shd.h
)

AUTO_BIND_SHADERS( shd )

ADD_EXECUTABLE(bullet ${SOURCES})
TARGET_LINK_LIBRARIES(bullet common ${LIBSL_LIBRARIES} ${LIBSL_GL_LIBRARIES} BulletCollision BulletDynamics LinearMath)
