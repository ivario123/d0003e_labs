#include <avr/io.h>
#include "avr/iom169p.h"
#include "../include/lcd_driver.h"
#include "../include/string.h"
#define TIMER_SCALING_1024 0b101
#define TIMER_SCALING_256  0b100
#define TIMER_SCALING_64   0b011
#define TIMER_SCALING_8    0b010
#define TIMER_SCALING_1    0b001
#define TIMER_STOP		   0b000

void init(void){
	// Setting power options
	CLKPR = 0x80;
	CLKPR = 0X00;
	
	
	// Setting the pre-sacling factor to 256
	TCCR1B = TCCR1B|TIMER_SCALING_256;
	
	// Setting the pull up
	PORTB = PORTB|(1<<7);
}

void next_prime(long *num){
	while(1)
	{
		if(*num >= 3){
			if (*num%2 == 0)
			*num++;
			else
			*num +=2;
		}
		else{
			*num++;
		}
		if(is_prime(*num)==1){
			return;
		}
		// Print string to screen
	}
}

void button(){
	uint8_t target_value = 0;
	LCDDR1 = LCDDR1|2;
	while(1){
		while(target_value != (PINB&(1<<7))>>7);
		while(target_value == (PINB&(1<<7))>>7);
		// Swap states
		if(((LCDDR1&2)^2)== 0){
			LCDDR1 = LCDDR1^2;
			LCDDR2 = LCDDR2|2;
		}
		else{
			LCDDR1 = LCDDR1|2;
			LCDDR2 = LCDDR2^2;
		}
	}

}
void toggle_button_2(){
	if((LCDDR13&1)== 1){
		LCDDR13 = LCDDR13^1;
		LCDDR18 = LCDDR18|1;
	}
	else{
		LCDDR13 = LCDDR13|1;
		LCDDR18 = LCDDR18^1;
	}
}


int check_interrupts(uint16_t target_time,uint16_t prev_time,uint8_t *buttonstate){
	
	
	
	// Checking the timer interrupt
	uint16_t time = (uint16_t)TCNT1;
    
    // Catches wrap around condition
	if(!((prev_time>target_time && time >= prev_time))){
		if(time >= target_time)
		{    
			target_time=time;
			toggle_led_2();
		}
	}
	
	// check if button state has changed
	if((1!=(PINB&(1<<7))>>7))
	{
		if(*buttonstate==0){
			*buttonstate=1;
		}
		
		if(*buttonstate == 2){
			toggle_button_2();
			*buttonstate = 0;
		}
	}
	else if(*buttonstate == 1){
		*buttonstate =2 ;
	}
	// Return target time
	return target_time;
	
}


void task_4(void){
	LCDDR13 = LCDDR13|1;
	uint16_t freq = 31250/2;									// The segment should turn on and of every half cycle i.e flicker with 2 Hz frequency
	volatile uint16_t target_time = TCNT1+freq;					// Target time, will wrap around just like the timer
	volatile uint16_t last_time = target_time-freq;				// Last time the timer triggered, useful to look for overflows
	uint8_t buttonstate = 1;									// Tracks button actions, event triggers on 3
	long num = 1;												// Last number checked
	
	while(1)
	{
		// Calculate the next prime
		//next_prime(&num);
		// Check if any interrupts have been triggered
		if(target_time != check_interrupts(target_time,last_time,&buttonstate)){
			
			// uints wrap around in the same way as the timer reg
			last_time = target_time;
			target_time+=freq;
		}
		
		
		//write_long(num);
	}
}

int main(void)
{
	init();
	init_lcd();
	//write_char('1',0);
	//write_char('4',1);
	//write_char('0',1);
	//write_char('3',8);
	//write_char('a',1);
	//write_char('1',2);
	
	//blink();
	//button();
	//primes();
	task_4();
	
	while(1){
	}
}