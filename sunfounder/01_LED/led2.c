#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

#define  LED_R_PIN    0
#define  LED_Y_PIN    2
#define  DELAY      1000

void init() {
	if(wiringPiSetup() == -1){ 
		printf("setup wiringPi failed!");
		exit(1); 
	}
	pinMode(LED_R_PIN, OUTPUT);
	pinMode(LED_Y_PIN, OUTPUT);

	printf("LED_R_PIN : GPIO %d (wiringPin)\ninit done.\n", LED_R_PIN); 
	printf("LED_Y_PIN : GPIO %d (wiringPin)\ninit done.\n", LED_Y_PIN); 
}

void setLed(int pin, int state) {
	digitalWrite(pin, state); 
} 

int main(int argc, char argv[]) {
	init();

	while(1){
		setLed(LED_R_PIN, LOW);
		setLed(LED_Y_PIN, HIGH);
		printf("led on\n");
		delay(DELAY);
		setLed(LED_R_PIN, HIGH); 
		setLed(LED_Y_PIN, LOW); 
		printf("led off\n");
		delay(DELAY);
	}

	return 0;
}

