physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 24
physics_size_y    = 24
physics_can_sleep = true
physics_rotation  = false


addanim('phacochere_gd.png',96)
addanim('phacochere_dg.png',96)



playanim('phacochere_gd.png',false) 



function step()

    if evolution < 200 then
		set_velocity_x(2)
    else
	    set_velocity_x(-2)
    end
	evolution = evolution + 1
	if evolution == 400 then
		evolution = 0
    end

end

function contact(with)
end

function onAnimEnd()
    if evolution < 180 then
		 playanim('phacochere_gd.png',false)
    elseif evolution < 380 then
		 playanim('phacochere_dg.png',false)
    else
	     playanim('phacochere_gd.png',false)
    end
   
 
end