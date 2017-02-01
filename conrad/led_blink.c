/* 
 * Conrad - LED blink
 */


#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include <stdlib.h>

#define LED_PIN 6
#define LED_ON 1
#define LED_OFF 0
#define MIN_DUR 50
#define MAX_DUR 300

int main(void) {
	unsigned int i;
	unsigned int t1,t2;
	time_t t;

	printf("Raspberry Pi blink\n");

	srand((unsigned)time(&t));    // initialize random nr gen

	if (wiringPiSetup() == -1)     // initialize wiringPi
		return 1;

	pinMode(LED_PIN, OUTPUT);      // set PIN LED_PIN to output

	for (i=0;i<30;i++) {
		t1 = rand()%(MAX_DUR-MIN_DUR)+MIN_DUR;
		t2 = rand()%(MAX_DUR-MIN_DUR)+MIN_DUR;
		digitalWrite(LED_PIN, LED_ON);
		delay(t1);
		digitalWrite(LED_PIN, LED_OFF);
		delay(t2);
		printf("t1=%d, t2=%d\n",t1,t2);
		if (i%5==0) {
			printf("counter=%d\n",i);
			fflush(stdout);
		}
	}
	return 0;

}
