cmake_minimum_required(VERSION 2.6)
project(transforms)

AUTO_BIND_SHADERS( shader_sh )

ADD_EXECUTABLE(transforms transforms.cpp shader_sh.h shader_sh.fp shader_sh.vp)
TARGET_LINK_LIBRARIES(transforms common ${LIBSL_LIBRARIES} ${LIBSL_GL_LIBRARIES})
