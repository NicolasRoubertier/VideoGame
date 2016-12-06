physics_center_x  =  0
physics_center_y  =  0
physics_size_x    = 12
physics_size_y    = 16
physics_can_sleep = false
physics_rotation  = false

addanim('snipe.run_left.png',32)
addanim('snipe.run_right.png',32)
addanim('snipe.turn_left_to_right.png',32)
addanim('snipe.turn_right_to_left.png',32)

playanim('snipe.run_left.png',true)
stopanim()

-- define a state variable which can be: 
-- 'wait_left', 'wait_right'
-- 'walk_left', 'walk_right'
-- 'turn_left', 'turn_right'

state = 'wait_left'

function step()

  -- update state
  if state == 'wait_left' or state == 'wait_right' then
    if Key_a then
	  if state == 'wait_left' then 
	    -- already in the correct orientation, just walk!
	    state = 'walk_left'
	    playanim('snipe.run_left.png',true)
	  else
	    -- uho, need to turn left
	    state = 'turn_left'
	    playanim('snipe.turn_right_to_left.png',false)
	  end
    elseif Key_d then
	  if state == 'wait_right' then 
	    -- already in the correct orientation, just walk!
	    state = 'walk_right'
	    playanim('snipe.run_right.png',true)
	  else
	    -- uho, need to turn right
	    state = 'turn_right'
	    playanim('snipe.turn_left_to_right.png',false)
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
	if state == 'walk_left' or state == 'turn_left' or state == 'wait_left' then
		attack(0, 0)
    else
		attack(0, 1)
    end
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
end

function onAnimEnd()
  if state == 'turn_left' then
    state = 'walk_left'
	playanim('snipe.run_left.png',true)
  end
  if state == 'turn_right' then
    state = 'walk_right'
	playanim('snipe.run_right.png',true)
  end
end
