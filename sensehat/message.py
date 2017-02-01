from sense_hat import SenseHat 
from time import sleep
from random import randint

sense = SenseHat()
#sense.show_message("Bussi", scroll_speed=0.05, text_colour=[255,255,0], back_colour=[0,0,255])
sense.show_letter("W", text_colour=[255,0,0])
sleep(3)
sense.clear()

