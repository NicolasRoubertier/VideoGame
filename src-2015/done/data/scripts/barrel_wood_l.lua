physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 18
physics_size_y    = 16
physics_can_sleep = true
physics_rotation  = true

addanim('Canon_wood_G.png',37)
playanim('Canon_wood_G.png',false)

function step()
 
    set_velocity_x = 0
	set_velocity_y = 0
	if evolution == 200 then
		throw_fire_ball(pos_x, pos_y, 0)
    end
	if evolution > 200 then
		evolution = 0
    end
	evolution = evolution + 1
end

function contact(with)

end

function onAnimEnd()
playanim('Canon_wood_G.png',false)
end
