#include "../include/lcd_driver.h"
#include <avr/interrupt.h>
#include <stdbool.h>
mutex button_print_mutex = MUTEX_INIT;
uint16_t * timer = (uint16_t *)0x84;
uint8_t button_counter;
// Just sets the Clock reg to zerio
void reset_timer(){
	*timer = 0;
}

// from lab2
void computePrimes(int pos) {
	long n;
	
	for(n = 1; ; n++) {
		if (is_prime((long)n)) {
			printAt(n, pos);
		}
	}
}
// from lab2
void printAt(long num, int pos) {
	
    write_char((num % 100) / 10 + '0', pos);
	pos++;
    write_char( num % 10 + '0', pos);
}
// This also uses a global counter and it works just fine
void button(void){
		// Using the mutexes would be a good safeguard in case that it spawns 2 buttons
		//lock(&button_print_mutex);
		button_counter++;
		printAt(button_counter,4);
		//unlock(&button_print_mutex);
}
// Blink thread just toggles the led, rest is handled by interrupt
void blink(void){
	toggle_led();
}
// Button int that spawns a new button thread
ISR(PCINT1_vect) {
	// Yield only on press, not release
	if(0!=(PINB&(1<<7))>>7)
	spawn(button,0);
}
// Timer int, that spawns a new blink thread
ISR(TIMER1_COMPA_vect){
	reset_timer();
	spawn(blink,0);
}
// Sollution to the last question
// A better one would be to set the cpu in to sleepmode and trigger wakeup on interrupt
void bussy_task(){
	while(1);
}
int main() {
	init_lcd();
	uint16_t * target_time = (uint16_t *)0x88;
	
	*target_time = 3906;												// Approximate form of .5s in clock cycles * 
	// reseting timer
	*timer = 0;
	spawn(computePrimes,0);
	spawn(bussy_task,0);
	
}
