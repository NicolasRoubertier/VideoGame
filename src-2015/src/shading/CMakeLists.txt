cmake_minimum_required(VERSION 2.6)
project(shading)

AUTO_BIND_SHADERS( shader_sh )

ADD_EXECUTABLE(shading shading.cpp shader_sh.h shader_sh.fp shader_sh.vp)
TARGET_LINK_LIBRARIES(shading common ${LIBSL_LIBRARIES} ${LIBSL_GL_LIBRARIES})
