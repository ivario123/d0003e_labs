/*
 * lab1.c
 *
 * Created: 2022-01-17 15:25:57
 * Author : Ivar J�nsson
 */ 

#include <avr/io.h>
#include "avr/iom169p.h"
#include "../include/lcd_driver.h"
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
	
	// Setting the pullup
	PORTB = PORTB|(1<<7);
	
	return success;
}
int blink(){
	
	// uint16t's wrap around in the same way for timer and normal addition
	while(1){
		while(((uint16_t)TCNT1)!= last_time+freq);
		last_time =(uint16_t)TCNT1;
		toggle_led();
	}
	return 0;
}
int button(){
	uint8_t prev_value = 1;
	
	while(1){
		while(prev_value!=(PINB&(1<<7))>>7);
		while(prev_value == (PINB&(1<<7))>>7);
		toggle_led();
	}
	
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





int main(void)
{
	if(success != init())
		while(1);	// Blink onboard LED or something indicating error
	if(success != init_lcd())
		while(1);	// Blink onboard LED or something indicating error
	//write_char('a',1);
	//blink();
	//button();
	//primes();
    while(1) 
    {	uint16_t freq = 31250/2;		// The segment should turn on and of every half cycle i.e flicker with 2 Hz frequenzy
	    uint16_t last_time = TCNT1;
		long num = 0;
		num = next_prime(num);
		
		uint8_t temp = three_least_significant(num);
		
		char buffer[10];
		int_to_str(temp,buffer);
		write_string(buffer,0);
		
		
    }
}

