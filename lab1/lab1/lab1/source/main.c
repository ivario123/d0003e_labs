#include <avr/io.h>
#include "avr/iom169p.h"
#include "../include/lcd_driver.h"
#include "../include/string.h"

// Prescaler settings lifted from the documentation
#define TIMER_SCALING_1024 0b101
#define TIMER_SCALING_256  0b100
#define TIMER_SCALING_64   0b011
#define TIMER_SCALING_8    0b010
#define TIMER_SCALING_1    0b001
#define TIMER_STOP		   0b000

/************************************************************************/
/*								TASK 1,2,3,4							*/
/************************************************************************/

void init(void){
	// Setting power options
	CLKPR = 0x80;
	CLKPR = 0X00;
	
	
	// Setting the pre-sacling factor to 256
	TCCR1B = TCCR1B|TIMER_SCALING_256;
	
	// Setting the pull up
	PORTB = PORTB|(1<<7);
}


/************************************************************************/
/*								TASK 3									*/
/************************************************************************/
void button(void){
	// Uses two busy wait loops to ensure that the switch needs to be pushed and released before event trigger
	
	// Could be scrapped, but changing this to a 1 makes the event trigger on button press not release. Does not work for first switch tho.
	uint8_t target_value = 0;
	// Set a default value
	LCDDR1 = LCDDR1|2;
	while(1){
		while(target_value != (PINB&(1<<7))>>7);
		while(target_value == (PINB&(1<<7))>>7);
		// check if bit 1 of LCDDR1 is high
		if(((LCDDR1&2)^2)== 0){
			// Turn LCDDR1 bit 1 low if it's high, else turn it high
			LCDDR1 = LCDDR1^2;
			// Turn LCDDR2 bit 1 high
			LCDDR2 = LCDDR2|2;
		}
		else{
			LCDDR1 = LCDDR1|2;
			LCDDR2 = LCDDR2^2;
		}
	}

}

/************************************************************************/
/*								TASK 4									*/
/************************************************************************/
void next_prime(long *num){
	// Computes the next prime, if is_prime is broken it loops infinitely. Terrible for real-time systems
	while(1)
	{
		// If number i smaller than 3, increment by 1
		// Else increment by 2 if the number is odd, else increment by 1
		if(*num >= 3){
			if (*num%2 == 0)
			*num++;
			else
			*num +=2;
		}
		else{
			*num++;
		}
		// Check if new number is a prime number
		if(is_prime(*num)==1){
			return;
		}
	}
}


void toggle_button_2(void){
	// Swap, if statement not needed but makes it a bit clearer
	if((LCDDR13&1)== 1){
		// Look at button
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
	// if plausible time
	if(target_time <= time){
		// If in valid range
		if((prev_time > target_time&& time =< prev_time)|| target_time > prev_time)//(prev_time < time && target_time <= time )||(prev_time > time && time >= target_time))
		{    
			// Register a timer event
			target_time=time;
		}
	}
	
	// check if button state has changed
	if((1!=(PINB&(1<<7))>>7))
	{
		// Buttonstate 0 means that the button has been pressed and released
		if(*buttonstate==0){
			*buttonstate=1;
		}
		// Buttonstate 2 means that the button was released before this event
		if(*buttonstate == 2){
			// Triggers event
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
	LCDDR13 = LCDDR13|1;										// Start value for the leds for switching
	uint16_t freq = 31250/2;									// The segment should turn on and of every half cycle i.e flicker with 2 Hz frequency
	volatile uint16_t target_time = TCNT1+freq;					// Target time, will wrap around just like the timer
	volatile uint16_t last_time = target_time-freq;				// Last time the timer triggered, useful to look for overflows
	uint8_t buttonstate = 1;									// Tracks button actions, event triggers on 3
	long num = 1;												// Last number checked
	
	while(1)
	{
		// Calculate the next prime
		next_prime(&num);
		// Check if any interrupts have been triggered
		if(target_time != check_interrupts(target_time,last_time,&buttonstate)){
			
			toggle_led_2();
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
	
	
	// We can't run all functions after one another since they all implement some sort of busy wait
	// This would stop the next function from running.
	// Thus we need to rewrite the functions blink, button, primes to one large loop and call the helper functions
	// From there.
	task_4();
	
	while(1){
	}
}