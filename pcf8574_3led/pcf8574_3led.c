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

// *** GLOBAL VARIABLES ***
char timestamp[TIMESTAMP_LENGTH];

// *** FUNCTION DECLARATIONS ***
void printUsage(void);
int init(void);
int createTimestamp(char* buffer);


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
	
	pinMode (PIN1, OUTPUT);
	pinMode (PIN2, OUTPUT);
	pinMode (PIN3, OUTPUT);
	
	digitalWrite(PIN1, LOW);
	digitalWrite(PIN2, LOW);
	digitalWrite(PIN3, LOW);		
	
    createTimestamp(timestamp);
	fprintf(stdout,"%s init\n", timestamp);
	fflush(stdout);

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
	init();

	while(1) {
		delay(500);
		digitalWrite(PIN1, HIGH);
		digitalWrite(PIN2, HIGH);
		digitalWrite(PIN3, HIGH);
		delay(500);
		digitalWrite(PIN1, LOW);
		digitalWrite(PIN2, LOW);
		digitalWrite(PIN3, LOW);		
	}

	exit(EXIT_SUCCESS);
	return 0;
}



