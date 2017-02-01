#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LED_RED 7    // BCM 4   wPi 7  GPIO.7
#define LED_YLW 1    // BCM 18  wPi 1  GPIO.1
#define LED_GRN 4    // BCM 23  wPi 4  GPIO.4
#define LED_BLU 5    // BCM 24  wPi 5  GPIO.5
#define BUTTON  6    // BCM 25  wPi 6  GPIO.6

#define LED_ON 1
#define LED_OFF 0


#define DEBUG 0

int tl_init();
int tl_state(int red, int ylw, int grn, int blu);
int tl_off();
int tl_on();

int tl_init() {
	int i;
        if (wiringPiSetup()==-1)
                return 1;
        pinMode(LED_RED, OUTPUT);
        pinMode(LED_YLW, OUTPUT);
        pinMode(LED_GRN, OUTPUT);
        pinMode(LED_BLU, OUTPUT);
	pinMode(BUTTON, INPUT);

        if (DEBUG) printf("DBG tl test sequence begin\n");
	for (i=0; i<4; i++) {
		tl_on();
		delay(200);
		tl_off();
		delay(200);
	}
       if (DEBUG) printf("DBG tl test sequence end\n");

       return 0;
}

int tl_off() {
        if (DEBUG) printf("DBG tl_off()\n");
        return tl_state(LED_OFF, LED_OFF, LED_OFF, LED_OFF);
}

int tl_on() {
        if (DEBUG) printf("DBG tl_on()\n");
        return tl_state(LED_ON, LED_ON, LED_ON, LED_ON);
}

int tl_state(int red, int ylw, int grn, int blu) {
        if (DEBUG) printf("DBG R=%d, Y=%d, G=%d, B=%d\n", red, ylw, grn, blu);

        digitalWrite(LED_RED, red);
        digitalWrite(LED_YLW, ylw);
        digitalWrite(LED_GRN, grn);
	digitalWrite(LED_BLU, blu);

        return 0;
}

int wait() {
	printf("Press button:\n");
	
	while(1) {
		while(digitalRead(BUTTON) == LOW) {
			delay(100);
		}
		printf("Button pressed!\n");
		tl_on();
		delay(1000);
		tl_off();
	}

	return 0;
}

int main(int argc, char* argv[]) {
	if (tl_init()!=0) return 1;

	delay(500);
	wait();

	return 0;
}


