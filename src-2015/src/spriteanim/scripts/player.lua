addanim('gripe.run_left.png',32)
addanim('gripe.run_right.png',32)
addanim('gripe.turn_left_to_right.png',32)
addanim('gripe.turn_right_to_left.png',32)

playanim('gripe.run_left.png',true)
stopanim()

-- define a state variable which can be: 
-- 'wait_left', 'wait_right'
-- 'walk_left', 'walk_right'
-- 'turn_left', 'turn_right'

state = 'wait_left'
speed_jump_x=100
speed_jump_y=200
retombe=0

function step()

  -- update state
  
  if (state == 'wait_left' or state == 'wait_right') then
    
	if Key_a then
	  if state == 'wait_left' then 
	    -- already in the correct orientation, just walk!
	    state = 'walk_left'
	    playanim('gripe.run_left.png',true)
	  else
	    -- uho, need to turn left
	    state = 'turn_left'
	    playanim('gripe.turn_right_to_left.png',false)
	  end

    elseif Key_z then
	  if state == 'wait_right' then 
	    -- already in the correct orientation, just walk!
	    state = 'walk_right'
	    playanim('gripe.run_right.png',true)
	  else
	    -- uho, need to turn right
	    state = 'turn_right'
	    playanim('gripe.turn_left_to_right.png',false)
	  end	
	end

  else
    
	if not Key_a and state == 'walk_left' then
	  state = 'wait_left'
	  stopanim()
    
	elseif not Key_z and state == 'walk_right' then
	  state = 'wait_right'
	  stopanim()
	end
  end

  if (state == 'wait_right') or (state == 'wait_left') then
    if Key_e then
	  if state == 'wait_right' then 
	    -- already in the correct orientation, just walk!
	    state = 'jump_right'
	    playanim('gripe.run_right.png',true)
	  else
	    -- uho, need to turn right
	    state = 'turn_right'
	    playanim('gripe.turn_left_to_right.png',false)
	  end
	end
  else

	if not Key_e and state == 'jump_right' then
	    state = 'wait_right'
	    stopanim()
		retombe=0
		speed_jump_x=100
		speed_jump_y=200
	end
  end

  -- walk if state is 'walk_*'
  if state == 'walk_left' then
    pos_x = pos_x - elapsed * 16 / 1000
  elseif state == 'walk_right' then
    print("a")
    pos_x = pos_x + elapsed * 16 / 1000

  elseif state == 'jump_right' then
    pos_x = pos_x + speed_jump_x / 100
	pos_y = pos_y + speed_jump_y / 100

	if retombe==0 then
	  if (speed_jump_x==0 or speed_jump_y==0) then
	    speed_jump_x=100
	    speed_jump_y=-200
		retombe=1
	  else
	    speed_jump_x = speed_jump_x - 1
        speed_jump_y = speed_jump_y - 2
	  end
	elseif retombe==1 then
	  speed_jump_x = speed_jump_x - 1
      speed_jump_y = speed_jump_y + 2

	  if speed_jump_x==0 then
	    retombe=2
		
	  end
	end
  end

end

function contact(with)
  
end

function onAnimEnd()
  if state == 'turn_left' then
    state = 'walk_left'
	playanim('gripe.run_left.png',true)
  end
  if state == 'turn_right' then
    state = 'walk_right'
	playanim('gripe.run_right.png',true)
  end
end
