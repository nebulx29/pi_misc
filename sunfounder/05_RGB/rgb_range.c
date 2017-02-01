#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <softPwm.h>

#define uint unsigned int
#define uchar unsigned char

#define LED_RED 0
#define LED_GRN 1
#define LED_BLU 2

#define DEBUG 0

void setColor(uint r, uint g, uint b);

int init() {
	printf("Sunfounder 05_RGB Range\nsetting up...\n");
	if (wiringPiSetup()==-1) {
		printf("setup wiringPi failed\n");
		return -1;
	}
	softPwmCreate(LED_RED, 0, 100);
	softPwmCreate(LED_GRN, 0, 100);
	softPwmCreate(LED_BLU, 0, 100);
	setColor(0,0,0);
	return 0;
}

void destroy() {
	setColor(0,0,0);
	delay(300);
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

void setColorDelay(uint r, uint g, uint b, uint d) {
	setColor(r,g,b);
	delay(d);
}

void setColorDelayDflt(uint r, uint g, uint b) {
	setColorDelay(r,g,b,100);
}

void loop() {
	int i,j,k;
	
	printf("Whites\n");
	for (i=0; i<255; i=i+10)
		setColorDelayDflt(i,i,i); // White
	printf("Reds\n");
	for (i=0; i<255; i=i+10)
		setColorDelayDflt(i,0,0); // Reds
	printf("Greens\n");
	for (i=0; i<255; i=i+10)
		setColorDelayDflt(0,i,0); // Greens
	printf("Blues\n");		
	for (i=0; i<255; i=i+10)
		setColorDelayDflt(0,0,i); // Blues
	printf("Reds+Greens\n");		
	for (i=0; i<255; i=i+10)
		setColorDelayDflt(i,i,0); 
	printf("Reds+Blues\n");		
	for (i=0; i<255; i=i+10)
		setColorDelayDflt(i,0,i); 
	printf("Greens+Blues\n");		
	for (i=0; i<255; i=i+10)
		setColorDelayDflt(0,i,i); 
		
}



int main(int argc, char* argv[]) {
	init();
	loop();
	destroy();
}