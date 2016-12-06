physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 9
physics_size_y    = 12
physics_can_sleep = true
physics_rotation  = true

addanim('Gravitron.png',28)
playanim('Gravitron.png',false)


function step()
if movement == 3 then
    if evolution < 50 then
		set_velocity_y(0)
		set_velocity_x(-2)
    elseif evolution > 10 then 
		life = 0
    end
	evolution = evolution + 1

end

if movement == 4 then
    if evolution < 50 then
		set_velocity_y(0)
		set_velocity_x(2)
    elseif evolution > 10 then 
		life = 0
    end
	evolution = evolution + 1

end

end

function contact(with)
	life = 0
end

function onAnimEnd()
  playanim('Gravitron.png',false)
end