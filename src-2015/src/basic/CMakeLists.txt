cmake_minimum_required(VERSION 2.6)
project(basic)

ADD_EXECUTABLE(basic basic.cpp)
TARGET_LINK_LIBRARIES(basic common ${LIBSL_LIBRARIES} ${LIBSL_GL_LIBRARIES})
