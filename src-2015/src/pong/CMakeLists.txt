cmake_minimum_required(VERSION 2.6)
project(pong)

ADD_EXECUTABLE(pong pong.cpp)
TARGET_LINK_LIBRARIES(pong common ${LIBSL_LIBRARIES} ${LIBSL_GL_LIBRARIES})
