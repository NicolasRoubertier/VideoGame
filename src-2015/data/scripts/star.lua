physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 12
physics_size_y    = 25
physics_can_sleep = true
physics_rotation  = true

addanim('graal.png',68)
playanim('graal.png', true)

function step()

end

function contact(with)
  if with == 1 then
    nbOfStars = nbOfStars + 1
  end 
end

function onAnimEnd()
playanim('graal.png', true)
end