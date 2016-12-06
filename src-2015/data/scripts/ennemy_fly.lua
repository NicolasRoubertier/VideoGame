physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 12
physics_size_y    = 12
physics_can_sleep = true
physics_rotation  = false


addanim('ennemy.png',32)




playanim('ennemy.png',false) 



function step()

    if evolution < 260 then
		
    else
	   set_force(0,9.8)
    end
	evolution = evolution + 1
	if evolution == 520 then
		evolution = 0
    end

end

function contact(with)
end

function onAnimEnd()
  playanim('ennemy.png',false)
    
   
 
end