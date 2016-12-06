physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 9
physics_size_y    = 9
physics_can_sleep = true
physics_rotation  = false


addanim('crab_gd.png',39)
addanim('crab_dg.png',39)



playanim('crab_gd.png',false) 



function step()

    if evolution < 200 then
		set_velocity_x(4)
    else
	    set_velocity_x(-4)
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
		 playanim('crab_gd.png',false)
    elseif evolution < 380 then
		 playanim('crab_dg.png',false)
    else
	     playanim('crab_gd.png',false)
    end
   
 
end