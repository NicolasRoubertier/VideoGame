physics_center_x  =  0
physics_center_y  =  0
physics_size_x    = 16
physics_size_y    = 16
physics_can_sleep = false
physics_rotation  = false

addanim('runspritegauche.png',32)
addanim('runspritedroite.png',32)
addanim('retournement1.png',24)
addanim('retournement.png',24)

playanim('runspritegauche.png',true)
stopanim()

-- define a state variable which can be: 
-- 'wait_left', 'wait_right'
-- 'walk_left', 'walk_right'
-- 'turn_left', 'turn_right'

fireball = 'true'

state = 'wait_left'

function step()

  -- update state
  if state == 'wait_left' or state == 'wait_right' then
    if Key_a then
	  if state == 'wait_left' then 
	    -- already in the correct orientation, just walk!
	    state = 'walk_left'
	    playanim('runspritegauche.png',true)
	  else
	    -- uho, need to turn left
	    state = 'turn_left'
	    playanim('retournement.png',false)
	  end
    elseif Key_d then
	  if state == 'wait_right' then 
	    -- already in the correct orientation, just walk!
	    state = 'walk_right'
	    playanim('runspritedroite.png',true)
	  else
	    -- uho, need to turn right
	    state = 'turn_right'
	    playanim('retournement1.png',false)
	  end
	end
  else
    if not Key_a and state == 'walk_left' then
	  state = 'wait_left'
	  stopanim()
    elseif not Key_d and state == 'walk_right' then
	  state = 'wait_right'
	  stopanim()
	end
  end

  if Key_z then
    if(fireball == 'true') then
		if state == 'walk_left' or state == 'turn_left' or state == 'wait_left' then
			attack(0, pos_x, pos_y, 0)
	    else
			attack(0, pos_x, pos_y, 1)
		end
		fireball = 'false'
    end		 
  end

  if fireball == 'false' then
	evolution = evolution + 1
  end

  if evolution >= 50 then
	evolution = 0
	fireball = 'true'
  end	 


  if Key_v and Key_d then
    set_jump(0,4,1.5,3.5,0,0)


  elseif Key_v and Key_a then

    set_jump(0,4,0,0,-1.5,3.5)

  elseif Key_v then
  	set_jump(0,4,0,0,0,0)
  end

  -- walk if state is 'walk_*'

  if state == 'walk_left' then
    set_walk(-2., -60)

  elseif state == 'walk_right' then
    set_walk(2, 60)
  end

set_correction(0.003,0.01)
end

function contact(with)
   if with == 2 then
     killingContact = true
   end 
  if with == 3 then
      score = score + 1
  end
  if with == -1 then
	 gemContact = true
  end
end

function onAnimEnd()
  if state == 'turn_left' then
    state = 'walk_left'
	playanim('runspritegauche.png',true)
  end
  if state == 'turn_right' then
    state = 'walk_right'
	playanim('runspritedroite.png',true)
  end
end
