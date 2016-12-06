cmake_minimum_required(VERSION 2.6)
project(helloworld)

ADD_EXECUTABLE(helloworld helloworld.cpp)
TARGET_LINK_LIBRARIES(helloworld common ${LIBSL_LIBRARIES} ${LIBSL_GL_LIBRARIES})

AUTO_BIND_SHADERS( ${SHADERS} )
