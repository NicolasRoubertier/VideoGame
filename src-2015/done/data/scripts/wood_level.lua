
-- main platform color
platform = color(255,0,0)
tile(platform, 'tile_wood.png', 0,0, 18,16 )
lborder = color(128,0,0)
tile(lborder, 'tile_wood.png', 0,0, 18,16 )
rborder = color(196,0,0)
tile(rborder, 'tile_wood.png', 0,0, 18,16 )

-- sign
tile(color(0,0,255), 'area01_level_tiles.png', 176,0, 32,32 )

-- load tile map
chosenMap = math.random(0,0)
tilemap('map'.. chosenMap .. '.png',16,16)

-- automatically add borders
for j=0,num_tiles_y()-1 do
  for i=0,num_tiles_x()-1 do
    if tileat(i,j) == platform and tileat(i+1,j) == color(0,0,0) then
	  set_tileat(i,j,rborder)
	end
    if tileat(i,j) == platform and tileat(i-1,j) == color(0,0,0) then
	  set_tileat(i,j,lborder)
	end
	if tileat(i,j) == color(255, 174, 201) then

		create_ennemies(i, j, 0)
    end
	if tileat(i,j) == color(181, 230, 29) then

		create_ennemies(i, j, 1)
    end
	if tileat(i,j) == color(0, 162, 232) then
		create_ennemies(i, j, 2)
    end
	if tileat(i,j) == color(163, 73, 164) then
		create_ennemies(i, j, 3)
    end
	if tileat(i,j) == color(255, 128, 0) then
		create_ennemies(i, j, 4)
    end
	if tileat(i,j) == color(239, 228, 176) then
	    print('a')
		create_ennemies(i, j, 5)
    end
	if tileat(i,j) == color(255, 201, 14) then
		create_stars(i, j, 0)
    end
	if tileat(i,j) == color(255, 255, 255) then
		create_gems(i, j, 0)
    end
  end
end
