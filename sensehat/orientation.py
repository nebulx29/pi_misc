from sense_hat import SenseHat
from time import sleep

sense = SenseHat()

while True:
    orientation = sense.get_orientation()
    pitch = orientation['pitch']
    roll = orientation['roll']
    yaw = orientation['yaw']
    print("pitch={0:.0f}, roll={1:.0f}, yaw={2:.0f}".format(pitch,yaw,roll))

