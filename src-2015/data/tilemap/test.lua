
-- main platform color
platform = color(255,0,0)
tile(platform, 'area01_level_tiles.png', 16,32, 16,16 )
lborder = color(128,0,0)
tile(lborder, 'area01_level_tiles.png', 48,0, 16,16 )
rborder = color(196,0,0)
tile(rborder, 'area01_level_tiles.png', 64,0, 16,16 )

-- sign
sign = color(0,0,255)
tile(sign, 'area01_level_tiles.png', 176,0, 32,32 )

-- load tile map
tilemap('map0.png',16,16)
