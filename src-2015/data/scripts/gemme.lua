physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 12
physics_size_y    = 20
physics_can_sleep = true
physics_rotation  = false

addanim('diamant.png',57)
playanim('diamant.png', true)

function step()

end

function contact(with)
	if with == 1 then
		 nbOfDiamonds = (nbOfDiamonds + 1) - math.floor((nbOfDiamonds + 1)/4)*4
  end 
end

function onAnimEnd()
playanim('diamant.png', true)
end