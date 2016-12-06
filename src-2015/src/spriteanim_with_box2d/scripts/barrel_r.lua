physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 18
physics_size_y    = 16
physics_can_sleep = true
physics_rotation  = true

addanim('Canon_met_D.png',37)
playanim('Canon_met_D.png',false)

function step()
	throw_fire_ball(pos_x, pos_y, 1)
end

function contact(with)

  end  
end

function onAnimEnd()
playanim('Canon_met_D.png',false)
end
