from sense_hat import SenseHat
from time import sleep

sense = SenseHat()

r = [255,0,0]
o = [255,127,0]
y = [255,255,0]
g = [0,255,0]
b = [0,0,255]
i = [75,0,130]
v = [159,0,255]
e = [0,0,0]

image = [
e,e,e,e,e,e,e,e,
e,e,e,r,r,e,e,e,
e,r,r,o,o,r,r,e,
r,o,o,y,y,o,o,r,
o,y,y,g,g,y,y,o,
y,g,g,b,b,g,g,y,
b,b,b,i,i,b,b,b,
b,i,i,v,v,i,i,b
]

sense.set_pixels(image)
sleep(1)
sense.set_rotation(90)
sleep(1)
sense.set_rotation(180)
sleep(1)
sense.set_rotation(270)
sleep(1)
sense.set_rotation(0)
sleep(1)

sleep(1)
sense.flip_h()
sleep(1)
sense.set_rotation(90)
sleep(1)
sense.flip_v()
sleep(1)
sense.clear()







