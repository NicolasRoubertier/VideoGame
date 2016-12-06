physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 18
physics_size_y    = 16
physics_can_sleep = true
physics_rotation  = false


addanim('spikes_ice.png',37)
addanim('spikes_met.png',37)
addanim('spikes_nat.png',37)
addanim('spikes_wood.png',37)
playanim('spikes_ice.png',false) 



function step()


end

function contact(with)
end

function onAnimEnd()
  
		 if field == 0 then 
	       playanim('spikes_ice.png',false) 
		 end

		 if field == 1 then 
			playanim('spikes_met.png',false) 
		 end

		 if field == 2 then 
			playanim('spikes_nat.png',false) 
		 end

		 if field == 3 then 
			playanim('spikes_wood.png',false) 
		 end

    
   
 
end