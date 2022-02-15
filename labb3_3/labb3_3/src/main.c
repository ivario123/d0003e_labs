#include "../include/lcd_driver.h"
#include <avr/interrupt.h>
#include <stdbool.h>
mutex button_print_mutex = MUTEX_INIT;
uint16_t * timer = (uint16_t *)0x84;
uint8_t button_counter;
void reset_timer(){
	*timer = 0;
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
		//lock(&button_print_mutex);
		button_counter++;
		printAt(button_counter,4);
		//unlock(&button_print_mutex);
}
void blink(void){
	toggle_led();
}

ISR(PCINT1_vect) {
	// Yield only on press, not release
	if(0!=(PINB&(1<<7))>>7)
	spawn(button,0);
}
ISR(TIMER1_COMPA_vect){
	reset_timer();
	spawn(blink,0);
}
void bussy_task(){
	while(1);
}
int main() {
	LCDDR13 = LCDDR13|1;
	init_lcd();
	uint16_t * target_time = (uint16_t *)0x88;
	
	*target_time = 3906;												// Approximate form of .5s in clock cycles * 
	// reseting timer
	*timer = 0;
	spawn(computePrimes,0);
	spawn(bussy_task,0);
	
}
