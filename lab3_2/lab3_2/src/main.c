#ifndef MYTEST_C
#define MYTEST_C
#include "../include/lcd_driver.h"
#include <avr/interrupt.h>
#include <stdbool.h>
mutex blink_mutex = MUTEX_INIT;
mutex button_mutex = MUTEX_INIT;
mutex primes_mutex = MUTEX_INIT;
mutex button_print_mutex = MUTEX_INIT;
uint16_t * timer = (uint16_t *)0x84;
uint8_t button_counter;
void reset_timer(){
	*timer = 0;
}
ISR(PCINT1_vect) {
	// Yield only on press, not release
		if(0!=(PINB&(1<<7))>>7)
			unlock(&button_mutex);
}
ISR(TIMER1_COMPA_vect){
	unlock(&blink_mutex);
	reset_timer();
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
void primes(void){
	long num = 0;
	while(1){
		next_prime(&num);
		write_long(num);
	}
	
}
void printAt(long num, int pos) {
	
    write_char((num % 100) / 10 + '0', pos);
	pos++;
    write_char( num % 10 + '0', pos);
}
void button(void){
	while(1){
		lock(&button_mutex);
		lock(&button_print_mutex);
		button_counter++;
		printAt(button_counter,4);
		unlock(&button_print_mutex);
	}
}
void blink(void){
	while(1){
		lock(&blink_mutex);
		toggle_led();
	}
}


int main() {
	LCDDR13 = LCDDR13|1;
	init_lcd();
	uint16_t * target_time = (uint16_t *)0x88;
	
	*target_time = 3906;												// Approximate form of 50ms in clock cycles * 
	// reseting timer
	*timer = 0;
	
	lock(&blink_mutex);
	lock(&button_mutex);
	lock(&primes_mutex);
	spawn(blink,(int)&blink_mutex);
	spawn(button,(int)&button_mutex);
	computePrimes(0);
	return 0;
}
#endif
