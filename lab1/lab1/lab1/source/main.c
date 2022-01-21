/*
 * lab1.c
 *
 * Created: 2022-01-17 15:25:57
 * Author : Ivar Jönsson
 */ 

#include <avr/io.h>
#include "avr/iom169p.h"
#include "../include/lcd_driver.h"


int init(void){
	// Setting power options
	CLKPR = 0x80;
	CLKPR = 0X00;
	
	return success;
}

int main(void)
{
	if(success != init())
		while(1);	// Blink onboard LED or something indicating error
	if(success != init_lcd())
		while(1);	// Blink onboard LED or something indicating error
    while (1) 
    {
		
    }
}

