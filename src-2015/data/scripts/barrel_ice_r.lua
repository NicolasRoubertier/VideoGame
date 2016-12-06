physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 13
physics_size_y    = 13
physics_can_sleep = true
physics_rotation  = false

addanim('Canon_ice_D.png',37)
playanim('Canon_ice_D.png',false)

function step()
 
    set_velocity_x = 0
	set_velocity_y = 0
	if evolution == 300 then
		throw_fire_ball(pos_x, pos_y, 1)
    end
	if evolution > 300 then
		evolution = 0
    end
	evolution = evolution + 1
end

function contact(with)

end

function onAnimEnd()
playanim('Canon_ice_D.png',false)
end
