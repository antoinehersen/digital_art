import math
fill(0)
gap = 50
for x in range(5):
    for y in range(5):
        size = (x+1) * 5 + (5 -y ) * 4
        oval( x* gap +( gap - size )/2, y*gap + (gap - size)/2 , size, size)