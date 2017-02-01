#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

#define  LED_PIN    0
#define  DELAY      1000

void init() {
	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		exit(1); 
	}
	pinMode(LED_PIN, OUTPUT);

	printf("LED_PIN : GPIO %d (wiringPin)\ninit done.\n", LED_PIN); 
}

void setLed(int pin, int state) {
	digitalWrite(pin, state); 
} 

int main(int argc, char argv[]) {
	init();

	while(1){
		setLed(LED_PIN, LOW);
		printf("led on\n");
		delay(DELAY);
		setLed(LED_PIN, HIGH); 
		printf("led off\n");
		delay(DELAY);
	}

	return 0;
}

