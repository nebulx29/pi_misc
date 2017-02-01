import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(25, GPIO.OUT)

print "on"
GPIO.output(25,1)
time.sleep(2)

print "off"
GPIO.output(25,0)
time.sleep(1)

print "on"
GPIO.output(25,1)
time.sleep(2)

print "off"
GPIO.output(25,0)

GPIO.cleanup()
