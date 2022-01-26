/*
 * lab1.c
 *
 * Created: 2022-01-17 15:25:57
 * Author : Ivar Jönsson
 */ 

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

int init(void){
	// Setting power options
	CLKPR = 0x80;
	CLKPR = 0X00;
	
	
	// Setting the pre-sacling factor to 256
	TCCR1B = TCCR1B|TIMER_SCALING_256;
	
	// Setting the pull up
	PORTB = PORTB|(1<<7);
	
	return success;
}

long next_prime(long num){
	while(1)
	{
		if(num >= 3){
			if (num%2 == 0)
			num++;
			else
			num +=2;
		}
		else{
			num++;
		}
		if(is_prime(num)==1){
			return num;
		}
		// Print string to screen
	}
}

int button(){
	uint8_t prev_value = 0;
	LCDDR1 = LCDDR1|2;
	while(1){
		while(prev_value!=(PINB&(1<<7))>>7);
		while(prev_value == (PINB&(1<<7))>>7);
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
int check_interrupts(uint16_t target_time,uint16_t prev_time,uint8_t *buttonstate){
	
	
	
	// Checking the timer interrupt
	uint16_t time = (uint16_t)TCNT1;
	
	
	if(target_time < time && !((prev_time>target_time&& time>prev_time)||time < target_time))
	{
		// Felet uppstår när tiden ligger mellan gamla tiden och max men mål tid har wrappat runt
		
		target_time=time;
		toggle_led();
	}
	// check if button state has changed
	if((1!=(PINB&(1<<7))>>7))
	{
		volatile int i = 0;
		if(*buttonstate==0){
			*buttonstate=1;
		}
		if(*buttonstate == 2){
			if((LCDDR1^2)== 0){
				LCDDR1 = LCDDR1^2;
				LCDDR2 = LCDDR2|2;
			}
			else{
				LCDDR1 = LCDDR1|2;
				LCDDR2 = LCDDR2^2;
			}
			*buttonstate = 0;
		}
		// Do button interrupt things
	}
	else if(*buttonstate == 1){
		*buttonstate =2 ;
	}
	// Return target time
	return target_time;
		
}


void task_4(void){
	LCDDR1 = LCDDR1|2;
	uint16_t freq = 31250/2;									// The segment should turn on and of every half cycle i.e flicker with 2 Hz frequency
	volatile uint16_t target_time = TCNT1+freq;					// Target time, will wrap around just like the timer
	volatile uint16_t last_time = target_time-freq;				// Last time the timer triggerd, useful to look for overflows
	uint8_t buttonstate = 0;									// Tracks button actions, event triggers on 3
	long num = 0;
    while(1) 
    {	
		// Calculate the next prime
		long new_num = 0;//next_prime(num);
		// Check if any interrupts have been triggered
		if(target_time != check_interrupts(target_time,last_time,&buttonstate)){
			
			// uints wrap around in the same way as the timer reg
			last_time = target_time;
			target_time+=freq;
		}
		// Do the other stuff
		if(new_num!=num){
			uint8_t temp = six_least_significant(new_num);
			char buffer[6];
			int_to_str(temp,buffer);
			write_string(buffer,0);
		}
		num = new_num;
    }
}

int main(void)
{
	if(success != init())
		blink();
	if(success != init_lcd())
		blink();
	//write_char('1',0);
	//write_char('4',1);
	//write_char('0',1);
	//write_char('1',2);
	
	//blink();
	//button();
	primes();
	//task_4();
	
	while(1){
		}
}

