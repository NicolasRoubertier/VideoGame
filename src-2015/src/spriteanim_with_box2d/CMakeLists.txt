cmake_minimum_required(VERSION 2.6)
project(spriteanim_with_box2d)

ADD_EXECUTABLE(spriteanim_with_box2d
  main.cpp 
  script.cpp 
  script.h
  tilemap.cpp
  tilemap.h
  entity.cpp
  entity.h
  background.cpp
  background.h
  physics.cpp
  physics.h
  sound.cpp
  sound.h
  ../../data/scripts/player1.lua
  ../../data/scripts/player2.lua
  ../../data/scripts/ennemy.lua
  ../../data/scripts/star.lua
  ../../data/scripts/ball0.lua
  ../../data/scripts/ball1.lua
  ../../data/scripts/ice_ball.lua
  ../../data/scripts/met_ball.lua
  ../../data/scripts/nat_ball.lua
  ../../data/scripts/wood_ball.lua
  ../../data/scripts/crabs.lua
  ../../data/scripts/ennemy_fly.lua
  ../../data/scripts/gemme.lua
  ../../data/scripts/fireball.lua
  ../../data/scripts/barrel_ice_l.lua
  ../../data/scripts/barrel_ice_r.lua
  ../../data/scripts/barrel_nat_l.lua
  ../../data/scripts/barrel_nat_r.lua
  ../../data/scripts/barrel_met_l.lua
  ../../data/scripts/barrel_met_r.lua
  ../../data/scripts/barrel_wood_l.lua
  ../../data/scripts/barrel_wood_r.lua
  ../../data/scripts/monster_ice.lua
  ../../data/scripts/monster_nat.lua
  ../../data/scripts/monster_wood.lua
  ../../data/scripts/monster_met.lua
  ../../data/scripts/spikes_ice.lua
  ../../data/scripts/spikes_met.lua
  ../../data/scripts/spikes_nat.lua
  ../../data/scripts/spikes_wood.lua
  ../../data/scripts/ice_level.lua
  ../../data/scripts/met_level.lua
  ../../data/scripts/nat_level.lua
  ../../data/scripts/wood_level.lua


)



TARGET_LINK_LIBRARIES(spriteanim_with_box2d common ${LIBSL_LIBRARIES} ${LIBSL_GL_LIBRARIES} lua luabind Box2D OpenAL32 libsndfile-1)


AUTO_BIND_SHADERS( ${SHADERS} )
 
