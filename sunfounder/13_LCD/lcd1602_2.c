#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <lcd.h>

unsigned char line1[]   = "0123456789ABCDEF";
unsigned char line2[]   = "0123456789ABCDEF";
int fd;

int init_led() {
	if (wiringPiSetup() == -1){
		exit(1);
	}

	fd = lcdInit(2,   // cols
	             16,  // rows
				 4,   // bits
				 2,   // RS pin
				 3,   // E pin
				 6,   // d0 
				 5,   // d1
				 4,   // d2
				 1,   // d3
				 0,   // d4
				 0,   // d5
				 0,   // d6
				 0    // d7
				); //see /usr/local/include/lcd.h
	//printf("%d", fd);
	if (fd == -1){
		printf("lcdInit 1 failed\n") ;
		return 1;
	}
	lcdClear(fd);	
}

int display_at_once(unsigned char line1[], unsigned char line2[]) {
	int i;
	lcdClear(fd);
	printf("[1] ");
	for(i=0; i<16; i++){
		printf("%c", line1[i]);
		lcdPosition(fd, i, 0);
		lcdPutchar(fd, *(line1+i));
	}
	printf("\n[2] ");
	for(i=0; i<16; i++){
		printf("%c", line2[i]);
		lcdPosition(fd, i, 1);
		lcdPutchar(fd, *(line2+i));
	}
	printf("\n");
	fflush(stdout);
}

int display_char_at_time(unsigned char line1[], unsigned char line2[], int t) {
	int i;
	lcdClear(fd);
	printf("[1] ");
	for(i=0; i<16; i++){
		printf("%c", line1[i]);
		lcdPosition(fd, i, 0);
		lcdPutchar(fd, *(line1+i));
		delay(t);
	}
	printf("\n[2] ");
	for(i=0; i<16; i++){
		printf("%c", line2[i]);
		lcdPosition(fd, i, 1);
		lcdPutchar(fd, *(line2+i));
		delay(t);
	}
	printf("\n");
	fflush(stdout);
}


int main(int argc, char* argv[]) {
	init_led();

	display_at_once(line1, line2);
	delay(3000);
	display_char_at_time(line1, line2, 200);
	
	delay(3000);
	lcdClear(fd);
	
	exit(0);
	return 0;
}
