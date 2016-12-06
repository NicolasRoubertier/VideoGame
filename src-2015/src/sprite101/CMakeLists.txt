cmake_minimum_required(VERSION 2.6)
project(sprite101)

ADD_EXECUTABLE(sprite101 main.cpp sprite.cpp sprite.h)
TARGET_LINK_LIBRARIES(sprite101 common ${LIBSL_LIBRARIES} ${LIBSL_GL_LIBRARIES})

AUTO_BIND_SHADERS( ${SHADERS} )
