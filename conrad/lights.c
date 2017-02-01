#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>

#define LED_BLU 4    // BCM 23  wPi 4  GPIO.4
#define LED_YLW 5    // BCM 24  wPi 5  GPIO.5
#define LED_GRN 6    // BCM 25  wPi 6  GPIO.6
#define LED_RED 10   // BCM 8   wPi 10 CE0

#define BTN_BLU 7    // BCM 4   wPi 7  GPIO.7
#define BTN_YLW 0    // BCM 17  wPi 0  GPIO.0
#define BTN_GRN 2    // BCM 27  wPi 2  GPIO.2
#define BTN_RED 3    // BCM 22  wPi 3  GPIO.3

#define LED_ON  1
#define LED_OFF 0

#define BTN_ON  1 
#define BTN_OFF 0

#define BLINK_COUNT  20
#define T_BLINK      200
#define INIT_BLINK   0

#define DEBUG 0

typedef struct ButtonStat {
	int blu;
	int ylw;
	int grn;
	int red;
} ButtonStat;

ButtonStat btn_stat;
pthread_t threads[4];
//int threadids[4] = {0,1,2,3};

int tl_init();
int tl_state(int red, int ylw, int grn, int blu);
int tl_off();
int tl_on();
void* tl_blink(void* l);


int tl_init() {
        printf("Initialisation start\n");
        int i;
        if (wiringPiSetup()==-1)
                return 1;
        pinMode(LED_RED, OUTPUT);
        pinMode(LED_YLW, OUTPUT);
        pinMode(LED_GRN, OUTPUT);
        pinMode(LED_BLU, OUTPUT);
        pinMode(BTN_BLU, INPUT);
        pinMode(BTN_YLW, INPUT);
        pinMode(BTN_GRN, INPUT);
        pinMode(BTN_RED, INPUT);

	if (INIT_BLINK) {
		for (i=0; i<4; i++) {
			tl_on();
			delay(200);
			tl_off();
			delay(200);
		}
	}

	btn_stat.blu = BTN_OFF;
	btn_stat.ylw = BTN_OFF;
	btn_stat.grn = BTN_OFF;
	btn_stat.red = BTN_OFF;

        printf("Initialisation done\n");

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

//
// usage: int tl_blink(int led) 
//
void* tl_blink(void* l) {    
	int led = (int)l;

	int i=0;
	printf("tl_blink(%d,%d)\n", led, BLINK_COUNT);
	for (i=0; i<BLINK_COUNT; i++) {
		digitalWrite(led, LED_ON);
		delay(T_BLINK);
		digitalWrite(led, LED_OFF);
		delay(T_BLINK);
	}
	return (void*)0;
}

int main(int argc, char* argv[]) {
	printf("main() started\n");
	void *status;

	tl_init();
	delay(1000);

	pthread_create(&threads[0], NULL, tl_blink, (void*)LED_BLU);
	delay(T_BLINK/4);
	pthread_create(&threads[1], NULL, tl_blink, (void*)LED_YLW);
	delay(T_BLINK/4);
	pthread_create(&threads[2], NULL, tl_blink, (void*)LED_GRN);
	delay(T_BLINK/4);
	pthread_create(&threads[3], NULL, tl_blink, (void*)LED_RED);
	delay(T_BLINK/4);

	pthread_join(threads[0], &status);
	pthread_join(threads[1], &status);
	pthread_join(threads[2], &status);
	pthread_join(threads[3], &status);

	printf("main() ended\n");
	return 0;
}





