cmake_minimum_required(VERSION 2.6)
project(spriteanim-done)

ADD_EXECUTABLE(spriteanim-done 
  main.cpp 
  script.cpp 
  script.h
  tilemap.cpp
  tilemap.h
  entity.cpp
  entity.h
  ./scripts/coin.lua
  ./scripts/player.lua
  ./scripts/ennemy.lua
  ./scripts/level.lua
)
  
TARGET_LINK_LIBRARIES(spriteanim-done common ${LIBSL_LIBRARIES} ${LIBSL_GL_LIBRARIES} lua luabind)

AUTO_BIND_SHADERS( ${SHADERS} )
 