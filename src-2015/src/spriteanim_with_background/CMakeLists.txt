cmake_minimum_required(VERSION 2.6)
project(spriteanim_with_background)

ADD_EXECUTABLE(spriteanim_with_background
  main.cpp 
  script.cpp 
  script.h
  tilemap.cpp
  tilemap.h
  entity.cpp
  entity.h
  background.cpp
  background.h
  ./scripts/coin.lua
  ./scripts/player.lua
  ./scripts/ennemy.lua
  ./scripts/level.lua
)
  
TARGET_LINK_LIBRARIES(spriteanim_with_background common ${LIBSL_LIBRARIES} ${LIBSL_GL_LIBRARIES} lua luabind)

AUTO_BIND_SHADERS( ${SHADERS} )
 