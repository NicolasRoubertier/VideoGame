physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 10
physics_size_y    = 10
physics_can_sleep = true
physics_rotation  = false


addanim('Monster_ice_D.png',37)
addanim('Monster_ice_G.png',37)
playanim('Monster_ice_D.png',false) 



function step()



    if evolution < 350 then
		set_velocity_x(1.5)
    else
	    set_velocity_x(-1.5)
    end
	evolution = evolution + 1
	if evolution == 630 then
		evolution = 0
    end

end

function contact(with)
end

function onAnimEnd()
    if evolution < 350 then
	       playanim('Monster_ice_D.png',false) 



    elseif evolution >= 350 then
	       playanim('Monster_ice_G.png',false) 


    end
   
 
end