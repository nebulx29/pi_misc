#include <wiringPi.h>
#include <stdio.h>

#define   SDI   0   //serial data input
#define   RCLK  1   //memory clock input(STCP)
#define   SRCLK 2   //shift register clock input(SHCP)

#define  NR_8  0x01
#define  CA_b  0x20
#define  LO    0x08
#define  LU    0x09



unsigned char SegCode[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x80};
//unsigned char SegCode[17] = {0x88,0x44,0x22,0x11,0x00,0x10,0x11,0x12,0x14,0x18,0x20,0x21,0x22,0x24,0x28,0x40,0x41};

void init(void)
{
	pinMode(SDI, OUTPUT); //make P0 output
	pinMode(RCLK, OUTPUT); //make P0 output
	pinMode(SRCLK, OUTPUT); //make P0 output

	digitalWrite(SDI, 0);
	digitalWrite(RCLK, 0);
	digitalWrite(SRCLK, 0);
}

void hc595_shift(unsigned char dat)
{
	int i;

	for(i=0;i<8;i++){
		digitalWrite(SDI, 0x80 & (dat << i));
		digitalWrite(SRCLK, 1);
		delay(1);
		digitalWrite(SRCLK, 0);
	}

		digitalWrite(RCLK, 1);
		delay(1);
		digitalWrite(RCLK, 0);
}

int main(int argc, char* argv[])
{
	int i;
	
	int val = atoi(argv[1]);
	char cval = (char)val;
	fprintf(stdout, "argv = %d %#x %c \n", cval, cval, cval);

	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		return 1; 
	}

	init();

	/*while(1){
		for(i=0;i<17;i++){
			hc595_shift(SegCode[i]);
			delay(500);
		}
	}*/
	
	hc595_shift(cval);
	delay(1000);

	return 0;
}

