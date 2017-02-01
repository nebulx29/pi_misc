#include <wiringPi.h>
#include <stdio.h>

#define   PIN_DATA   0   // DS      data  - serial data input
#define   PIN_STORE  1   // ST_CP   store - memory clock input(STCP)
#define   PIN_SHIFT  2   // SH_CP   shift - shift register clock input(SHCP)

unsigned char LED[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

void pulse(int pin) {
	digitalWrite(pin, LOW);
	digitalWrite(pin, HIGH);
}

void store() {
	pulse(PIN_STORE);
}

void shift() {
	pulse(PIN_SHIFT);
}

void SIPO(unsigned char byte) {
	int i;

	for(i=0;i<8;i++){
		digitalWrite(PIN_DATA, ((byte & (0x80 >> i)) > 0));
		shift();
	}
}

void display(unsigned char byte) {
	fprintf(stdout, "display(%#x | %d)\n", byte, byte);
	SIPO(byte);
	store();
}

int init(void) {
	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		return 1; 
	}	
	
	pinMode(PIN_DATA, OUTPUT);   
	pinMode(PIN_STORE, OUTPUT);  
	pinMode(PIN_SHIFT, OUTPUT); 

	digitalWrite(PIN_DATA, LOW);
	digitalWrite(PIN_STORE, LOW);
	digitalWrite(PIN_SHIFT, LOW);
	fprintf(stdout, "init done\n");
	return 0;
}

void blink(int times, int delay_ms) {
	int i;
	for (i=0; i<times; i++) {
		display(0xFF);
		delay(delay_ms);
		display(0x00);
		delay(delay_ms);		
	} 
}

int main(void) {
	int i;
	unsigned char byte;
	
	init();
	
	//blink(5, 50);
	
	delay(1000);
	byte = 0xFF;
	for (i=0; i<=255; i++) {
		display(i);
		delay(100);
	}
	delay(2000);
	
	//blink(5, 50);

	return 0;
}

