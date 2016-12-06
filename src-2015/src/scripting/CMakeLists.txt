cmake_minimum_required(VERSION 2.6)
project(scripting)

ADD_EXECUTABLE(scripting scripting.cpp)
TARGET_LINK_LIBRARIES(scripting common ${LIBSL_LIBRARIES} ${LIBSL_GL_LIBRARIES} lua luabind)
