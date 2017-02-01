#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <sys/time.h>

#define PIN_1  0  // rechts oben
#define PIN_2 27  // rechts unten
#define PIN_3 28  // unten
#define PIN_4 29  // links unten
#define PIN_5 24  // links oben
#define PIN_6  2  // oben
#define PIN_7 25  // mitte
#define PIN_8 26  // dot

#define LOOP_DELAY  50
#define DEBUG 0
#define TIMESTAMP_LENGTH 27


char timestamp[TIMESTAMP_LENGTH];

int createTimestamp(char* buffer);
int segment7_write(int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8);
int segment7_all_off();
int segment7_all_on();
int segment7(int i);


int init(void) {
    if(wiringPiSetup() < 0){
    	fprintf(stderr, "Unable to setup wiringPi:%s\n",strerror(errno));
		return 1;
    }
	pinMode(PIN_1, OUTPUT);
	pinMode(PIN_2, OUTPUT);
	pinMode(PIN_3, OUTPUT);
	pinMode(PIN_4, OUTPUT);
	pinMode(PIN_5, OUTPUT);
	pinMode(PIN_6, OUTPUT);
	pinMode(PIN_7, OUTPUT);
	pinMode(PIN_8, OUTPUT);
	segment7_all_off();
	return 0;
}

int segment7_write(int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8) {
	digitalWrite(PIN_1, i1);
	digitalWrite(PIN_2, i2);
	digitalWrite(PIN_3, i3);
	digitalWrite(PIN_4, i4);
	digitalWrite(PIN_5, i5);
	digitalWrite(PIN_6, i6);
	digitalWrite(PIN_7, i7);
	digitalWrite(PIN_8, i8);
	return 0;
}

int segment7_all_off() {
	segment7_write(LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW);
}

int segment7_all_on() {
	segment7_write(HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH);
}

int segment7(int i) {
	switch(i) {
		case 0:
			segment7_write(HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW);
			break;
		case 1:
			segment7_write(HIGH, HIGH, LOW, LOW, LOW, LOW, LOW, LOW);
			break;
		case 2:
			segment7_write(HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH, LOW);
			break;
		case 3:
			segment7_write(HIGH, HIGH, HIGH, LOW, LOW, HIGH, HIGH, LOW);
			break;
		case 4:
			segment7_write(HIGH, HIGH, LOW, LOW, HIGH, LOW, HIGH, LOW);
			break;
		case 5:
			segment7_write(LOW, HIGH, HIGH, LOW, HIGH, HIGH, HIGH, LOW);
			break;
		case 6:
			segment7_write(LOW, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW);
			break;
		case 7:
			segment7_write(HIGH, HIGH, LOW, LOW, LOW, HIGH, LOW, LOW);
			break;
		case 8:
			segment7_write(HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW);
			break;
		case 9:
			segment7_write(HIGH, HIGH, LOW, LOW, HIGH, HIGH, HIGH, LOW);
			break;
		default:
			fprintf(stderr, "Invalid parameter. digit '%d'\n");
			return 1;
	}
	return 0;
}

int display(int i) {
	fprintf(stdout, "%d ", i);
	segment7(i);	
	delay(1000);
}


int main (void) {
	int i;
	
	init();
	
	display(9);
	display(8);
	display(7);
	display(6);
	display(5);
	display(4);
	display(3);
	display(2);
	display(1);
	display(0);
	
	for (i=0; i<10; i++) {
		segment7_all_off();
		delay(100);
		segment7_all_on();
		delay(100);
	}
	segment7_all_off();

	return 0;
}

int createTimestamp(char* buffer) {
  /*int millisec;
  struct tm* tm_info;
  struct timeval tv;
  char buffer2[TIMESTAMP_LENGTH];
  
  gettimeofday(&tv, NULL);

  millisec = lrint(tv.tv_usec/1000.0); 
  if (millisec>=1000) { 
    millisec -=1000;
    tv.tv_sec++;
  }

  tm_info = localtime(&tv.tv_sec);
  strftime(buffer, TIMESTAMP_LENGTH, "%Y-%m-%d %H:%M:%S", tm_info); 
  sprintf(buffer, "%s.%d", buffer, millisec);*/
	return 0;
}