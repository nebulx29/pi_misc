/* 
 * Conrad - LED blink - Morse Alphabet
 */


#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LED_PIN 6
#define LED_ON 1
#define LED_OFF 0

#define DEBUG 0

#define S_DOT    '.'
#define S_DASH   '-'

#define T_UNIT   200
#define T_DOT    1*T_UNIT   // length of dot is one unit
#define T_DASH   3*T_UNIT   // length of dash is three units
#define T_SYMB   1*T_UNIT   // space between symbols is one unit
#define T_LETTER 3*T_UNIT   // space between letters is three units
#define T_WORD   7*T_UNIT   // space between words is seven units

int writeSymbol(char s);
int writeLetter(char c);
int writeWord(char* c);
char* charToSymbol(char c);

char* codes[] =       {".-",      //  0 = A ('A' = ASCII code 65; 'a' = ASCII code 97)
		       "-...",    //  1 = B
		       "-.-.",    //  2 = C
		       "-..",     //  3 = D
		       ".",       //  4 = E
		       "..-.",    //  5 = F
		       "--.",     //  6 = G
		       "....",    //  7 = H
		       "..",      //  8 = I
		       ".---",    //  9 = J
		       "-.-",     // 10 = K
		       ".-..",    // 11 = L
		       "--",      // 12 = M
		       "-.",      // 13 = N
		       "---",     // 14 = O
		       ".--.",    // 15 = P
		       "--.-",    // 16 = Q
		       ".-.",     // 17 = R
		       "...",     // 18 = S
		       "-",       // 19 = T
		       "..-",     // 20 = U
		       "...-",    // 21 = V
		       ".--",     // 22 = W
		       "-..-",    // 23 = X
		       "-.--",    // 24 = Y
		       "--..",    // 25 = Z
		       "-----",   // 26 = 0 (ASCII code 48)
		       ".----",   // 27 = 1
		       "..---",   // 28 = 2
		       "...--",   // 29 = 3
		       "....-",   // 30 = 4
		       ".....",   // 31 = 5
		       "-....",   // 32 = 6
		       "--...",   // 33 = 7
		       "---..",   // 33 = 8
		       "----.",   // 34 = 9
		       "--..--",  // 36 = , (ASCII code 44)
		       ".-.-.-"   // 37 = . (ASCII code 46)
	      };

char* charToSymbol(char c) {
	c = toupper(c);	
	if (c >= 'A' && c <= 'Z') {
		return codes[c-'A'];
	} else if (c >= '0' && c <= '9') {
		return codes[c - '0' + 26];
	} else if (c == ',') {
		return codes[36];
	} else if (c == '.') {
		return codes[37];
	} else {
		return "*";
	}
}

int writeSymbol(char s) {
	if (DEBUG) printf("    writeSymbol(%c)\n",s);
	digitalWrite(LED_PIN, LED_ON);
	if (s!=S_DOT && s!=S_DASH) {
		printf("    writeSymbol: invalid parameter: s=%c",s);
		return 1;
	}
	delay(s==S_DOT ? T_DOT : T_DASH);
	digitalWrite(LED_PIN, LED_OFF);
	delay(T_SYMB);
	return 0;
}

int writeLetter(char c) {
	char* s = charToSymbol(c);
	int i;
	int len = strlen(s);
	if (DEBUG) printf("  writeLetter('%c') = '%s' (len=%i)\n", c, s, len);
	for (i=0; i<len; i++) {
		writeSymbol(s[i]);
	}
	delay(T_LETTER);
	printf("%s ",s);
	fflush(stdout);
	return 0;
}

int writeWord(char* word) {
	int i;
	int len = strlen(word);
	printf("%s\n",word);
	for (i=0; i<len; i++) {
		writeLetter(word[i]);
	}
	delay(T_WORD);
	return 0;
}



int main(int argc, char* argv[]) {
	printf("\n\n");
	if (wiringPiSetup() == -1)     // initialize wiringPi
		return 1;
	pinMode(LED_PIN, OUTPUT);      // set PIN LED_PIN to output

	writeWord(argv[1]);

	printf("\n\n");
	return 0;

}
