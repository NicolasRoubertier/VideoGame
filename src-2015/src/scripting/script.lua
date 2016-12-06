
-- global section

player = spawn(64,64,'Character Boy')
gem1 = spawn(256,256,'Gem Blue')
gem2 = spawn(300,512,'Gem Blue')

-- functions

function step()

  if Key_w then
    move(player,0,1)
  end
  if Key_a then
    move(player,-1,0)
  end
  if Key_s then
    move(player,0,-1)
  end
  if Key_d then
    move(player,1,0)
  end

end

function contact(u,v)
   log('entity ' .. u .. ' touches entity ' .. v)
end




















