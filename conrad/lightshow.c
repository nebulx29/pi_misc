#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>

#define LED_BLU 0
#define LED_GRN 1
#define LED_YLW 2
#define LED_RED 3

#define BTN_BLU 0
#define BTN_GRN 1
#define BTN_YLW 2
#define BTN_RED 3

#define OFF 0
#define ON 1

int LEDS[] = {4, 5, 6, 10}; 
int BTNS[] = {7, 2, 0, 3};

int tl_init();
int tl_off();
int tl_on();
int tl_sequ1();
int tl_sequ2();
int tl_sequ3();
int tl_sequ4();

int tl_init() {
        printf("Initialisation start\n");
        int i;
        if (wiringPiSetup()==-1)
                return 1;

	for (i=0; i<4; i++)
		pinMode(LEDS[i], OUTPUT);
	for (i=0; i<4; i++)
		pinMode(BTNS[i], INPUT);

        tl_off();
        for (i=0; i<4; i++) {
		tl_on();
		delay(200);
		tl_off();
		delay(200);
	}

        printf("Initialisation done\n");
        delay(1000);

        return 0;
}

int tl_on() {
	int i;
	for (i=0; i<4; i++)
		digitalWrite(LEDS[i], ON);
	return 0;
}

int tl_off() {
	int i;
	for (i=0; i<4; i++)
		digitalWrite(LEDS[i], OFF);
	return 0;
}

int tl_state(int blu, int grn, int ylw, int red) {
	digitalWrite(LEDS[LED_BLU], blu);
	digitalWrite(LEDS[LED_GRN], grn);
	digitalWrite(LEDS[LED_YLW], ylw);
	digitalWrite(LEDS[LED_RED], red);
	return 0;
}


int tl_sequ1() {
	int i;
	for (i=0; i<20; i++) {
		tl_on();
		delay(100);
		tl_off();
		delay(100);
	}
	return 0;
}

int tl_sequ2() {
	int i,j;
	tl_off();
	for (i=0; i<20; i++) {
		for (j=0; j<4; j++) {
			digitalWrite(LEDS[j], ON);
			delay(50);
			digitalWrite(LEDS[j], OFF);
		}
	}
	return 0;
}

int tl_sequ3() {
	int i;
	tl_off();
	for (i=0; i<8; i++) {
		tl_state(OFF, ON, ON, OFF);
		delay(200);
		tl_state(OFF, OFF, OFF, OFF);
		delay(200);
		tl_state(ON, OFF, OFF, ON);
		delay(200);
		tl_state(OFF, OFF, OFF, OFF);
		delay(200);
	}
	return 0;
}

int tl_sequ4() {
	int i;
	tl_off();
	for (i=0; i<2; i++) {
		tl_state(ON, OFF, OFF, OFF);
		delay(200);
		tl_state(ON, ON, OFF, OFF);
		delay(200);
		tl_state(ON, ON, ON, OFF);
		delay(200);
		tl_state(ON, ON, ON, ON);
		delay(200);
		tl_state(OFF, ON, ON, ON);
		delay(200);
		tl_state(OFF, OFF, ON, ON);
		delay(200);
		tl_state(OFF, OFF, OFF, ON);
		delay(200);
		tl_state(OFF, OFF, OFF, OFF);
		delay(200);
		tl_state(OFF, OFF, OFF, ON);
		delay(200);
		tl_state(OFF, OFF, ON, ON);
		delay(200);
		tl_state(OFF, ON, ON, ON);
		delay(200);
		tl_state(ON, ON, ON, ON);
		delay(200);
		tl_state(ON, ON, ON, OFF);
		delay(200);
		tl_state(ON, ON, OFF, OFF);
		delay(200);
		tl_state(ON, OFF, OFF, OFF);
		delay(200);
		tl_state(OFF, OFF, OFF, OFF);
		delay(200);
	}
	return 0;
}

int main(int argc, char* argv[]) {
	printf("main() started\n");
	tl_init();

	while(1) {
		if (digitalRead(BTNS[BTN_BLU])==ON)
			tl_sequ1();
		if (digitalRead(BTNS[BTN_YLW])==ON)
			tl_sequ2();
		if (digitalRead(BTNS[BTN_GRN])==ON)
			tl_sequ3();
		if (digitalRead(BTNS[BTN_RED])==ON)
			tl_sequ4();
		delay(200);
	}

	printf("main() end\n");
	return 0;
}





