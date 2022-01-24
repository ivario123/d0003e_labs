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
	
	
	// Setting the presacling factor to 256
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
		else
		num++;
		if(is_prime(num)==1){
			return num;
		}
		// Print string to screen
	}
}

int button(){
	uint8_t prev_value = 1;
	int state = 0;
	while(1){
		while(prev_value != (PINB&(1<<7))>>7);
		while(prev_value == (PINB&(1<<7))>>7);
		state=!state;
		
		if((LCDDR1^2)== 0){
			LCDDR1 = 0;
			LCDDR2 = 2;
		}
		else{
			LCDDR1 = 2;
			LCDDR2 = 0;
		}
		
	}

}
int check_interrupts(uint16_t freq,uint16_t last_time,uint8_t *buttonstate){
	// Checking timer int
	uint16_t time = (uint16_t)TCNT1;
	volatile uint16_t max = ~0;
	// grabs wrap around condition too
	if(time >= last_time+freq ^ (max-last_time+time > freq&& last_time!=0))
	{
		volatile last_time = time;
		toggle_led();
	}
	
	// check if button state has changed
	if((*buttonstate!=(uint8_t)PINB)^(1!=(PINB&(1<<7))>>7))
	{
		volatile int i = 0;
		if((LCDDR1^2)== 0){
			LCDDR1 = 0;
			LCDDR2 = 2;
		}
		else{
			LCDDR1 = 2;
			LCDDR2 = 0;
		}
		// Do button interrupt things
		*buttonstate= (uint8_t)PINB;
	}
	
		
}


int main(void)
{
	if(success != init())
		while(1);	// Blink on board LED or something indicating error
	if(success != init_lcd())
		while(1);	// Blink on board LED or something indicating error
	//write_char('a',1);
	//blink();
	button();
	//primes();
	
	
	uint16_t freq = 31250/2;		// The segment should turn on and of every half cycle i.e flicker with 2 Hz frequency
	uint16_t last_time = TCNT1;
	uint8_t buttonstate = 1;
	long num = 0;
    while(1) 
    {	
		// Calculate the next prime
		long new_num = 0;//next_prime(num);
		// Check if any interrupts have been triggered
		last_time = check_interrupts(31250/2,last_time,&buttonstate);
		// Do the other stuff
		if(new_num!=num){
			uint8_t temp = six_least_significant(num);
			char buffer[4];
			int_to_str(temp,buffer);
			write_string(buffer,0);
			last_time = check_interrupts(freq,last_time,&buttonstate);
		}
		num = new_num;
		
		
		
    }
}

