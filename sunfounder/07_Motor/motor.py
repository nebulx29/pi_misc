#!/usr/bin/env python

import RPi.GPIO as GPIO
import time
import os

MOTOR_PIN1 = 17
MOTOR_PIN2 = 27
MOTOR_SWITCH = 24
DEBUG = True

def init():
    if (DEBUG==True): 
        print "DBG init()"
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(MOTOR_PIN1, GPIO.OUT)
    GPIO.setup(MOTOR_PIN2, GPIO.OUT)
    GPIO.setup(MOTOR_SWITCH, GPIO.OUT)
    GPIO.output(MOTOR_PIN1, GPIO.LOW)
    GPIO.output(MOTOR_PIN2, GPIO.LOW)
    GPIO.output(MOTOR_SWITCH, GPIO.LOW)

def destroy():
    if (DEBUG==True): 
        print "DBG destroy()"
    GPIO.output(MOTOR_PIN1, GPIO.LOW)
    GPIO.output(MOTOR_PIN2, GPIO.LOW)
    GPIO.output(MOTOR_SWITCH, GPIO.LOW)
    GPIO.cleanup()

def motor_off():
    if (DEBUG==True): 
        print "DBG motor_off()"
    GPIO.output(MOTOR_SWITCH, GPIO.LOW)
    
def motor_on():
    if (DEBUG==True): 
        print "DBG motor_on()"
    GPIO.output(MOTOR_SWITCH, GPIO.HIGH)
    
def motor_clockwise():
    if (DEBUG==True): 
        print "DBG motor_clockwise()"
    GPIO.output(MOTOR_PIN1, GPIO.HIGH)
    GPIO.output(MOTOR_PIN2, GPIO.LOW)
    
def motor_counterclockwise():
    if (DEBUG==True): 
        print "DBG motor_counterclockwise()"
    GPIO.output(MOTOR_PIN1, GPIO.LOW)
    GPIO.output(MOTOR_PIN2, GPIO.HIGH)
    
def loop():
    if (DEBUG==True):
        print "DBG loop()"
    while True:
        print "clockwise"
        motor_clockwise()
        motor_on()
        time.sleep(3)
        motor_off()
        time.sleep(1)
        print "counterclockwise"
        motor_counterclockwise()
        motor_on()
        time.sleep(3)
        motor_off()  
        time.sleep(1)  

if __name__ == '__main__':
    init()
    try:
        loop()
    except KeyboardInterrupt:
        destroy()
