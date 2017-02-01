#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>

#define LED_RED 10
#define LED_YLW 6
#define LED_GRN 5
#define LED_BLU 4
#define BUTTON  7    // BCM 25  wPi 6  GPIO.6

#define LED_ON 1
#define LED_OFF 0

#define DEBUG 0

#define T_PHASE_BLU_BLINK 500
#define T_PHASE_RED  5000
#define T_PHASE_REDYLW 1500
#define T_PHASE_GRN 5000
#define T_PHASE_GRN_BLINK 500
#define T_PHASE_YLW 1500

int tl_init();
int tl_state(int red, int ylw, int grn, int blu);
int tl_trf_state(int red, int ylw, int grn);
int tl_ped_state(int blu);
int tl_off();
int tl_on();
void* tl_sequence(void*);

int s_ped_active;
int s_ready_4_ped;

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

int tl_trf_state(int red, int ylw, int grn) {
	if (DEBUG) printf("DBG R=%d, Y=%d, G=%d\n", red, ylw, grn);
	digitalWrite(LED_RED, red);
	digitalWrite(LED_YLW, ylw);
	digitalWrite(LED_GRN, grn);
	return 0;
}

int tl_ped_state(int blu) {
	if (DEBUG) printf("DBG B=%d\n", blu);
	digitalWrite(LED_BLU, blu);
	return 0;
}

void* tl_sequence(void* threadid) {
	long tid = (long)threadid;
	int i;
	if (1) printf("DBG tl_sequence(%d)\n", (int)tid);
	printf("tl_sequence: s_ped_active=%d\n",s_ped_active);

	while (TRUE) {
		tl_trf_state(LED_ON, LED_OFF, LED_OFF);   // RED
		s_ready_4_ped=1;
		delay(T_PHASE_RED);
		while (s_ped_active) {
			delay(T_PHASE_RED);
		}
		s_ready_4_ped=0;
		tl_trf_state(LED_ON, LED_ON, LED_OFF);    // RED-YLW
		delay(T_PHASE_REDYLW);
		tl_trf_state(LED_OFF, LED_OFF, LED_ON);   // GREEN
		delay(T_PHASE_GRN);
		tl_trf_state(LED_OFF, LED_OFF, LED_OFF);  // ALL OFF
		for (i=0; i<4; i++) {
			delay(T_PHASE_GRN_BLINK);
			tl_trf_state(LED_OFF, LED_OFF, LED_ON);   // GREEN
			delay(T_PHASE_GRN_BLINK);
			tl_trf_state(LED_OFF, LED_OFF, LED_OFF);  // ALL OFF
		}
		tl_trf_state(LED_OFF, LED_ON, LED_OFF);   // YELLOW
		delay(T_PHASE_YLW);
	}
	pthread_exit(NULL);
}

void* tl_sequence_ped_light(void *threadid) {
	long tid = (long)threadid;
	int i;
	if (1) printf("DBG tl_sequence_ped_light(%d)\n", (int)tid);
	printf("tl_sequence_ped_light: s_ped_active=%d\n",s_ped_active);
	for (i=0; i<10; i++) {
		tl_ped_state(LED_ON);
		delay(T_PHASE_BLU_BLINK);
		tl_ped_state(LED_OFF);
		delay(T_PHASE_BLU_BLINK);
	}
	if (1) printf("DBG tl_sequence_ped_light() terminating thread\n");
	s_ped_active=0;
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	pthread_t threads[2];
	int rc1=0, rc2=0;
	s_ped_active=0;
	s_ready_4_ped=0;
	void* status;

	if (tl_init()!=0) return 1;

	do {
		rc1= pthread_create(&threads[0], NULL, tl_sequence, (void*)0);
		delay(500);
		while(digitalRead(BUTTON) == LOW) {
			delay(100);
		}
		printf("Button pressed. Starting Pedestrian Light.\n");
		s_ped_active=1;
		while(!s_ready_4_ped) {
			delay(200);
		}
		rc2 = pthread_create(&threads[1], NULL, tl_sequence_ped_light, (void*)1);
		pthread_join(threads[1], &status);
		s_ped_active=0;
		s_ready_4_ped=0;
	} while (1);

	if (DEBUG) printf("%d,%d\n", rc1,rc2);

	while(1) { 
		delay(100);
	}
	return 0;
}
