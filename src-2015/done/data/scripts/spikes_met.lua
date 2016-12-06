physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 18
physics_size_y    = 16
physics_can_sleep = true
physics_rotation  = false



addanim('spikes_met.png',37)

playanim('spikes_met.png',false) 



function step()


end

function contact(with)
end

function onAnimEnd()
  
playanim('spikes_met.png',false) 

    
   
 
end