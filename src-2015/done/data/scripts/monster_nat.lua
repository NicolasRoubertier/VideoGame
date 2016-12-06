physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 18
physics_size_y    = 16
physics_can_sleep = true
physics_rotation  = false



addanim('Monster_nat_D.png',37)
addanim('Monster_nat_G.png',37)

playanim('Monster_nat_D.png',false) 



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
    if evolution < 200 then
	
			playanim('Monster_nat_D.png',false) 


    elseif evolution >= 200 then

			playanim('Monster_nat_G.png',false) 


    end
   
 
end