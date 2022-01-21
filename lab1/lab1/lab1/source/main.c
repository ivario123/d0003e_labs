/*
 * lab1.c
 *
 * Created: 2022-01-17 15:25:57
 * Author : Ivar Jönsson
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

int button(){
	uint8_t prev_value = 1;
	
	while(1){
		while(prev_value!=(PINB&(1<<7))>>7);
		while(prev_value == (PINB&(1<<7))>>7);
		toggle_led();
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
	button();
    while(1) 
    {
		
    }
}

