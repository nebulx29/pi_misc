#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

#define LED_PIN 1

int led_pwm(int dutyCycle) {
	pwmWrite(LED_PIN, dutyCycle);
	delay(2);
}

int led_on() {
	digitalWrite(LED_PIN, HIGH);
}

int led_off() {
	digitalWrite(LED_PIN, LOW);
}

int init() {
	printf("setting up...\n");
	if (wiringPiSetup()==-1) {
		printf("setup wiringPi failed\n");
		return -1;
	}
	pinMode(LED_PIN, PWM_OUTPUT);
	led_off();
	return 0;
}

int destroy() {
	printf("cleaning up...\n");
	return 0;
}

int loop() {
	int i;
	while (1) {
		for (i=0; i<1024; i++) {
			led_pwm(i);
		}
		for (i=1023; i>=0; i--) {
			led_pwm(i);
		}
	}
	return 0;
}

int main(int argc, char* argv[]) {
	init();
	loop();
	destroy();
}