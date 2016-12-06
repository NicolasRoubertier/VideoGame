physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 15
physics_size_y    = 15
physics_can_sleep = true
physics_rotation  = true

addanim('Star.png',30)
playanim('Star.png', true)

function step()

end

function contact(with)
	if with == 1 then
    nbOfStars = nbOfStars + 1
  end 
end

function onAnimEnd()
playanim('Star.png', true)
end