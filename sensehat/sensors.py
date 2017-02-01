from sense_hat import SenseHat
from time import sleep

sense = SenseHat()

while True:
    t = sense.get_temperature()
    p = sense.get_pressure()
    h = sense.get_humidity()

    t = round(t, 1)
    p = round(p, 1)
    h = round(h, 1)

    #msg = "T={0} P={1} H={2}".format(t,p,h)
    print("T={0} P={1} H={2}".format(t,p,h))
    sleep(1)

#    sense.show_message(msg, scroll_speed=0.05)
#	print(msg)
#	sleep(1)
