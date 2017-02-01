import RPi.GPIO as GPIO
import time

LED_PIN = 12

def setup():
    global p
    GPIO.setmode(GPIO.BOARD)  # physical location
    GPIO.setup(LED_PIN, GPIO.OUT)
    led_off();
    
def led_off():
    GPIO.output(LED_PIN, GPIO.LOW)

def led_on():
    GPIO.output(LED_PIN, GPIO.HIGH)
    
def destroy():
    led_off()
    GPIO.cleanup()
    
if __name__ == '__main__':
    setup()
    time.sleep(1)
    led_on()
    time.sleep(1)
    led_off()
    time.sleep(1)
    led_on()
    time.sleep(1)
    destroy()
    
