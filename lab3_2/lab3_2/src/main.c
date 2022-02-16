#ifndef MYTEST_C
#define MYTEST_C
#include "../include/lcd_driver.h"
#include <avr/interrupt.h>
#include <stdbool.h>
// Relevant mutexes ( could be moved to seperate file )
mutex blink_mutex = MUTEX_INIT;
mutex button_mutex = MUTEX_INIT;
mutex primes_mutex = MUTEX_INIT;
uint16_t * timer = (uint16_t *)0x84;
// Global button counter, just as in part 1 but this one works
uint8_t button_counter;
void reset_timer(){
	*timer = 0;
}
// From lab2
void printAt(long num, int pos) {
	
    write_char((num % 100) / 10 + '0', pos);
	pos++;
    write_char( num % 10 + '0', pos);
}
// ISR for the button pin
ISR(PCINT1_vect) {
	// Yield only on only one of the edges
		if(0!=PINB>>7)
			unlock(&button_mutex);
}
//  Timer interrupt to unlock the blink mutex
ISR(TIMER1_COMPA_vect){
	unlock(&blink_mutex);
	reset_timer();
}
// From lab2
void computePrimes(int pos) {
	long n;
	for(n = 1; ; n++) {
		if (is_prime((long)n)) {
			printAt(n, pos);
		}
	}
}
// Loops around and relocks mutex after finnish
void button(int pos){
	while(1){
		
		printAt(button_counter,pos);
		lock(&button_mutex);
		button_counter++;
	}
}
// Loops around and relocks after finnish
void blink(int a){
	while(1){
		lock(&blink_mutex);
		toggle_led();
	}
}


int main() {
	// initiating the LCD
	init_lcd();
	// Setting a pointer to the TCINT CMP register
	uint16_t * target_time = (uint16_t *)0x88;
	*target_time = 3906;												// Approximate form of 50ms in clock cycles * 
	// reseting timer
	*timer = 0;
	// Mutex setup
	lock(&blink_mutex);
	lock(&button_mutex);
	lock(&primes_mutex);
	// Spawns the threads
	spawn(blink,0);
	spawn(button,4);
	// spawn main thread i.e. a bussy task
	computePrimes(0);
}
#endif
