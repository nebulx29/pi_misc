#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define LED_PIN   0
#define BTN_PIN   1
#define DELAY     10

void init() {
        if(wiringPiSetup() == -1){
                printf("setup wiringPi failed!");
                exit(1);
        }
        pinMode(LED_PIN, OUTPUT);
        pinMode(BTN_PIN, INPUT);

        printf("LED_PIN : GPIO %d (wiringPin) OUT \ninit done.\n", LED_PIN);
        printf("BTN_PIN : GPIO %d (wiringPin) IN \ninit done.\n", LED_PIN);
	digitalWrite(LED_PIN, LOW);
	// pullUpDnContorl(BTN_PIN, PUD_UP); 
}

int main(int argc, char* argv[]) {
	int b;
	init();
	while(1) {
		b = digitalRead(BTN_PIN);
		digitalWrite(LED_PIN, (b==1?LOW:HIGH));
		delay(DELAY);
	}
	return 0;
}

