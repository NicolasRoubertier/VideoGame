physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 8
physics_size_y    = 8
physics_can_sleep = true
physics_rotation  = true

addanim('spinning_coin_red.png',16)
playanim('spinning_coin_red.png',false)


function step()
if movement == 1 then
    if evolution < 50 then
		set_velocity_y(3)
		set_velocity_x(0)
    elseif evolution > 50 then 
		set_velocity_y(-3)
		set_velocity_x(0)
    end
	evolution = evolution + 1
	if evolution == 100 then
		evolution = 0
    end

end

if movement == 2 then
    if evolution < 50 then
		set_velocity_y(0)
		set_velocity_x(3)
    elseif evolution > 50 then 
		set_velocity_y(0)
		set_velocity_x(-3)
    end
	evolution = evolution + 1
	if evolution == 100 then
		evolution = 0
    end

end

end

function contact(with)
end

function onAnimEnd()
  playanim('spinning_coin_red.png',false)
end