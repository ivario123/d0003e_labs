#ifndef MYTEST_C
#define MYTEST_C
#include "../include/tinythreads.h"
#include "../include/lcd_driver.h"
mutex print_mutex = MUTEX_INIT;
// From lab 2
void printAt(long num, int pos) {
	lock(&print_mutex);
    write_char((num % 100) / 10 + '0', pos);
    write_char( num % 10 + '0', pos+1);
	unlock(&print_mutex);
}
// From lab 2
void computePrimes(int pos) {
    long n;
	
    for(n = 1; ; n++) {
        if (is_prime((long)n)) {
            printAt(n, pos);
        }
    }
}
// Access function as a last resort
void next_prime(long *num){
	while(1)
	{
		*num+=1;
		if(is_prime(*num)==1){
			return;
		}
	}
}

uint8_t button_thingy = 0;
// Access function as a last resort
void increment_button_thingy(){
	button_thingy++;
}
// Access function as a last resort
uint8_t get_button_thingy(){
	return button_thingy;
}
void button(int arg){
		
		/*
		// This one works, don't know why
		uint8_t * ptr = 0x83E9;
		while(1){
			while(0==(PINB&(1<<7))>>7);
			printAt(*ptr,4);
			*ptr = *ptr+1;
			while(1==(PINB&(1<<7))>>7);
			
		}*/
		// This one does not work. I don't know why
		//	uint8_t *ptr = &button_thingy;
		while(1){
			while(1 == (PINB&(1<<7))>>7);
			increment_button_thingy();
			//*ptr = *ptr + 1;
			printAt(get_button_thingy(),4);
			while(0 == (PINB&(1<<7))>>7);
		}
		
}
void blink(int arg){
	while(1){
		if(get_timer_int_counter() >= 10){
			reset_timer_int_counter();
			toggle_led();
		}
	}
}
int main() {
	LCDDR13 = LCDDR13|1;
	init_lcd();
	
	spawn(button,0);
    spawn(blink,0);	
	computePrimes(0);
	while(1);
}
#endif
