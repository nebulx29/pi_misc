/***
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <wiringPi.h>
#include <pcf8574.h>

// *** CONSTANTS ***
#define PIN_BASE 128
#define PIN1 PIN_BASE+0
#define PIN2 PIN_BASE+1
#define PIN3 PIN_BASE+2
#define DEBUG 0
#define TIMESTAMP_LENGTH 27
#define PIN_SIG_WAIT 50
#define LOOP_WAIT 100

// *** GLOBAL VARIABLES ***
char timestamp[TIMESTAMP_LENGTH];
//int flag1=0,flag2=0,flag3=0;

// *** FUNCTION DECLARATIONS ***
void printUsage(void);
int init(void);
int createTimestamp(char* buffer);
int readPin(int pin);
	
// *** FUNCTION DEFINITONS ***
void printUsage() {
	fprintf(stderr, "Usage: mmctrl\n"
		            "  TODO\n"
		);
	exit(EXIT_FAILURE);
}


int init(void) {
	int i;
	if (wiringPiSetup()<0) {
		fprintf(stderr, "Unable to setup wiringPi: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
		return 1;
	}
	
	pcf8574Setup (PIN_BASE, 0x20);
	
	pinMode (PIN1, INPUT);
	pinMode (PIN2, INPUT);
	pinMode (PIN3, INPUT);
	
	pullUpDnControl(PIN1, PUD_UP);
	pullUpDnControl(PIN2, PUD_UP);
	pullUpDnControl(PIN3, PUD_UP);
	
    createTimestamp(timestamp);
	fprintf(stdout,"%s init\n", timestamp);
	fflush(stdout);

	return 0;
}

/* 
 * returns true if PIN is low for 
 */
int readPin(int pin) {
	int v = digitalRead(pin);
	if (digitalRead(pin)==LOW) {
		delay(PIN_SIG_WAIT);
		if (digitalRead(pin)==LOW) {
			return 1;
		}
	}
	return 0;
}


int createTimestamp(char* buffer) {
  int millisec;
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
  strftime(buffer, TIMESTAMP_LENGTH, "%Y%m%d %H:%M:%S", tm_info); 
  sprintf(buffer, "%s.%d", buffer, millisec);
}

int main(int argc, char* argv[]) {
	int p[] = {0,0,0};
	int i;
	
	init();

	while(1) {
		for(i=0; i<3; i++) {
			p[i] = readPin(PIN1+i);
		}
		//if ((p[0]+p[1]+p[2])>0)
			fprintf(stdout, "%d %d %d\n",p[0],p[1],p[2]);
		
		delay(LOOP_WAIT);		
	}

	exit(EXIT_SUCCESS);
	return 0;
}



