#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LED_RED 7    // BCM 4   wPi 7  GPIO.7
#define LED_YLW 1    // BCM 18  wPi 1  GPIO.1 
#define LED_GRN 4    // BCM 23  wPi 4  GPIO.4
#define LED_ON 1
#define LED_OFF 0

#define DEBUG 0

int tl_init();
int tl_state(int red, int ylw, int grn);
int tl_off();
int tl_on();
int tl_sequence();

int tl_init() {
	if (wiringPiSetup()==-1)
		return 1;
	pinMode(LED_RED, OUTPUT);
	pinMode(LED_YLW, OUTPUT);
	pinMode(LED_GRN, OUTPUT);

	if (DEBUG) printf("DBG tl test sequence begin\n");
	tl_on();
	delay(200);
	tl_off();
	delay(200);
	tl_on();
	delay(200);
	tl_off();
	delay(200);
	tl_on();
	delay(200);
	tl_off();
	delay(200);
	if (DEBUG) printf("DBG tl test sequence end\n");

	return 0;
}

int tl_off() {
	if (DEBUG) printf("DBG tl_off()\n");
	return tl_state(LED_OFF, LED_OFF, LED_OFF);
}

int tl_on() {
	if (DEBUG) printf("DBG tl_on()\n");
	return tl_state(LED_ON, LED_ON, LED_ON);
}

int tl_state(int red, int ylw, int grn) {
	if (DEBUG) printf("DBG R=%d, Y=%d, G=%d\n", red, ylw, grn);

	digitalWrite(LED_RED, red);
	digitalWrite(LED_YLW, ylw);
	digitalWrite(LED_GRN, grn);

	return 0;
}

int tl_sequence() {
	int t_phase_red = 5000;
	int t_phase_redylw = 1500;
	int t_phase_grn = 5000;
	int t_phase_grn_blink = 500;
	int t_phase_ylw = 1500;
	
	if (DEBUG) printf("DBG tl_sequence()\n");

	while (TRUE) {
		tl_state(LED_ON, LED_OFF, LED_OFF);   // RED
		delay(t_phase_red);
		tl_state(LED_ON, LED_ON, LED_OFF);    // RED-YLW
		delay(t_phase_redylw);
		tl_state(LED_OFF, LED_OFF, LED_ON);   // GREEN
		delay(t_phase_grn);
		tl_state(LED_OFF, LED_OFF, LED_OFF);  // ALL OFF
		delay(t_phase_grn_blink);
		tl_state(LED_OFF, LED_OFF, LED_ON);   // GREEN 1
		delay(t_phase_grn_blink);
		tl_state(LED_OFF, LED_OFF, LED_OFF);  // ALL OFF
		delay(t_phase_grn_blink);
		tl_state(LED_OFF, LED_OFF, LED_ON);   // GREEN 2 
		delay(t_phase_grn_blink);
		tl_state(LED_OFF, LED_OFF, LED_OFF);  // ALL OFF
		delay(t_phase_grn_blink);
		tl_state(LED_OFF, LED_OFF, LED_ON);   // GREEN 3
		delay(t_phase_grn_blink);
		tl_state(LED_OFF, LED_OFF, LED_OFF);  // ALL OFF
		delay(t_phase_grn_blink);
		tl_state(LED_OFF, LED_OFF, LED_ON);   // GREEN 4
		delay(t_phase_grn_blink);
		tl_state(LED_OFF, LED_OFF, LED_OFF);  // ALL OFF
		delay(t_phase_grn_blink);
		tl_state(LED_OFF, LED_ON, LED_OFF);   // YELLOW
		delay(t_phase_ylw);
	}
}

int main(int argc, char* argv[]) {
	if (tl_init()!=0) return 1;

	tl_sequence();

	return 0;
}
