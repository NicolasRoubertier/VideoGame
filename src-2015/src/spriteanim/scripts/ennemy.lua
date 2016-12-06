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

function step()

  -- update state
  
  if (state == 'wait_left' or state == 'wait_right') then
    if Key_l then
	  if state == 'wait_left' then 
	    -- already in the correct orientation, just walk!
	    state = 'walk_left'
	    playanim('gripe.run_left.png',true)
	  else
	    -- uho, need to turn left
	    state = 'turn_left'
	    playanim('gripe.turn_right_to_left.png',false)
	  end
    elseif Key_m then
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
    if not Key_l and state == 'walk_left' then
	  state = 'wait_left'
	  stopanim()
    elseif not Key_m and state == 'walk_right' then
	  state = 'wait_right'
	  stopanim()
	end
  end



  -- walk if state is 'walk_*'
  if state == 'walk_left' then
    pos_x = pos_x - elapsed * 16 / 1000
  elseif state == 'walk_right' then
    pos_x = pos_x + elapsed * 16 / 1000
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