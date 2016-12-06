cmake_minimum_required(VERSION 2.6)
project(tilemap)

ADD_EXECUTABLE(tilemap 
  main.cpp 
  script.cpp 
  script.h
  tilemap.cpp
  tilemap.h
)
  
TARGET_LINK_LIBRARIES(tilemap common ${LIBSL_LIBRARIES} ${LIBSL_GL_LIBRARIES} lua luabind)

AUTO_BIND_SHADERS( ${SHADERS} )
