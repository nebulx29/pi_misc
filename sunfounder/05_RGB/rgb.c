#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <softPwm.h>

#define uint unsigned int

#define LED_RED 0
#define LED_GRN 1
#define LED_BLU 2

#define DEBUG 1


int init() {
	printf("Sunfounder 05_RGB\nsetting up...\n");
	if (wiringPiSetup()==-1) {
		printf("setup wiringPi failed\n");
		return -1;
	}
	softPwmCreate(LED_RED, 0, 100);
	softPwmCreate(LED_GRN, 0, 100);
	softPwmCreate(LED_BLU, 0, 100);
	return 0;
}

void destroy() {
	exit(0);
}

float color_perc(uint c) {
	return ((float)c/255.0f)*100.0f;
}

void setColor(uint r, uint g, uint b) {     // color range: 0..255
	if (DEBUG) printf("setColor(RGB: %3d %3d %3d | %2x %2x %2x | %3.0f %3.0f %3.0f)\n",r,g,b,r,g,b,color_perc(r), color_perc(g), color_perc(b));
	softPwmWrite(LED_RED, r);
	softPwmWrite(LED_GRN, g);
	softPwmWrite(LED_BLU, b);
}

void loop() {
	
	while(1){
		setColor(0xff,0x00,0x00);   //red	
		delay(500);
		setColor(0x00,0xff,0x00);   //green
		delay(500);
		setColor(0x00,0x00,0xff);   //blue
		delay(500);

		setColor(0xff,0xff,0x00);   //yellow
		delay(500);
		setColor(0xff,0x00,0xff);   //pick
		delay(500);
		setColor(0xc0,0xff,0x3e);
		delay(500);

		setColor(0x94,0x00,0xd3);
		delay(500);
		setColor(0x76,0xee,0x00);
		delay(500);
		setColor(0x00,0xc5,0xcd);	
		delay(500);

	}
}



int main(int argc, char* argv[]) {
	init();
	loop();
	destroy();
}