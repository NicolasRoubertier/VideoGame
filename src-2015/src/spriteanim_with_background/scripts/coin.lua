addanim('spinning_coin_gold.png',16)
playanim('spinning_coin_gold.png',false)

function step()

end

function contact(with)
  if with == 'player' then
    killed = true
  end  
end

function onAnimEnd()
  playanim('spinning_coin_gold.png',false)
end
