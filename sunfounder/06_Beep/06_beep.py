#!/usr/bin/env python
import RPi.GPIO as GPIO
import time

BEEP_PIN = 17    # GPIO.0 / BCM 17 / Physical 11

def setup():
	GPIO.setmode(GPIO.BCM)           # Numbers GPIOs by BCM location
	GPIO.setup(BEEP_PIN, GPIO.OUT)   # Set BeepPin's mode is output
	GPIO.output(BEEP_PIN, GPIO.HIGH) # Set BeepPin high(+3.3V) to off beep

def loop():
    while True:
        for i in range(10,100,10):
            print "i=%d" % (i)
            GPIO.output(BEEP_PIN, GPIO.LOW)
            time.sleep(i/10)
            GPIO.output(BEEP_PIN, GPIO.HIGH)
            time.sleep(i/10)

def destroy():
	GPIO.output(BEEP_PIN, GPIO.HIGH)    # beep off
	GPIO.cleanup()                      # Release resource

if __name__ == '__main__':     # Program start from here
	print 'Press Ctrl+C to end the program...'
	setup()
	try:
		loop()
	except KeyboardInterrupt:  
		destroy()

