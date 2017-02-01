import RPi.GPIO as GPIO
import time

LED_PIN = 12

def setup():
    global p
    GPIO.setmode(GPIO.BOARD)  # physical location
    GPIO.setup(LED_PIN, GPIO.OUT)
    led_off();
    p = GPIO.PWM(LED_PIN, 1000) # frequency = 1khz
    p.start(0)
    
def led_off():
    GPIO.output(LED_PIN, GPIO.LOW)

def led_on():
    GPIO.output(LED_PIN, GPIO.HIGH)
    
def destroy():
    led_off()
    GPIO.cleanup()
    
def loop():
    while True:
        for dc in range(0,101,4):
            p.ChangeDutyCycle(dc)
            time.sleep(0.02)
        #time.sleep(1)
        for dc in range(100,-1,-4):
            p.ChangeDutyCycle(dc)
            time.sleep(0.02)
        #time.sleep(1)
    
if __name__ == '__main__':
    setup()
    loop()
    destroy()
    
