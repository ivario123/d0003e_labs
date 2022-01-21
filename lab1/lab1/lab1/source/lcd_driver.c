/*
 * lcd_driver.c
 *
 * Created: 2022-01-21 08:21:07
 *  Author: ivarj
 */ 

#include "../include/lcd_driver.h"
#include <stdint-gcc.h>
#include <avr/io.h>
int write_char(char ch,int pos){
	if(pos >MAX_POS||pos<MIN_POS)
	return -1;
	// The address of the first segment of the display
	LCDDR0 = A;
	// The numbers 0-9, credit wikipedia might be wrong
	return success;
}

int init_lcd(){
		
		
		//-----------------------------------
		// Status manipulation
		//-----------------------------------
		// enabling the lcd
		LCDCRA = LCDCRA|(1<<LCDEN);
		// Setting low power wave form
		LCDCRA = LCDCRA|(1<<LCDAB);
		// disabling the interrupt
		LCDCRA = LCDCRA&(~(1<<LCDIF));
		// Disabling blanking
		LCDCRA = LCDCRA&(~(1));
		
		
		//-----------------------------------
		// Clock manipulation
		//-----------------------------------
		
		// setting the clock source to external
		LCDCRB = LCDCRB&(~(1<<LCDCS));
		// Setting Bias
		LCDCRB = LCDCRB&(~(1<<LCD2B));
		// Setting duty cycle
		LCDCRB = LCDCRB&(~(3<<LCDMUX0));
		// Setting number of active segments to 25
		LCDCRB = LCDCRB|(3);
		
		
		//-----------------------------------
		// Frame rate manipulation
		//-----------------------------------
		// Set n = 16
		LCDFRR = LCDFRR&(~(8<<LCDPS0));
		// Set D = 8
		LCDFRR = LCDFRR||(8);
		
		
		//-----------------------------------
		// Contrast manipulation
		//-----------------------------------
		// Setting msb->msb-2 to 0 to set drive time to 300 us
		LCDCCR = LCDCCR&(~(8<< LCDDC0));
		// Setting lsb -> lsb+3 to 1 to set voltage to 3.35V 
		LCDCCR = LCDCCR&((16));
		
		
		
		
		
		// Setting the contrast voltage to3.35v and drive time to 300ms
		//*LCDCCR = (*LCDCCR)&0b11111000;
		// Setting the
		//*LCDFRR = (*LCDFRR)&0b10001111;
		return success;
}