#ifndef MYTEST_C
#define MYTEST_C
#include "../include/tinythreads.h"
#include "../include/lcd_driver.h"
#include <stdbool.h>


int pp = 0;
mutex pp_mutex = MUTEX_INIT; 
//void writeChar(char ch, int pos); // from lab 1

//bool is_prime(long i); // from lab 1

volatile void printAt(long num, int pos) {
	
    write_char((num % 100) / 10 + '0', pos);
    write_char( num % 10 + '0', pos+1);
}
void computePrimes(int pos) {
    long n;
	
    for(n = 1; ; n++) {
        if (is_prime((long)n)) {
            printAt(n, pos);
        }
    }
}
void next_prime(long *num){
	while(1)
	{
		*num+=1;
		if(is_prime(*num)==1){
			return;
		}
	}
}

volatile uint8_t button_counter = 0;
void button(){
		
		// Uses two busy wait loops to ensure that the switch needs to be pushed and released before event trigger
		uint8_t * ptr = 0x83E9;
		//uint8_t * ptr = &button_counter;
		while(1){
			while(0==(PINB&(1<<7))>>7);
			*(ptr) = *ptr +1;
			printAt(*ptr,4);
			while(1==(PINB&(1<<7))>>7);
		}
}

int main() {
	LCDDR13 = LCDDR13|1;
	init_lcd();
	
    spawn(blink,0);	
	spawn(button,0);
	computePrimes(0);
	return 0;
}
#endif
