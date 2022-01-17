/*
 * lab1.c
 *
 * Created: 2022-01-17 15:25:57
 * Author : Ivar Jönsson
 */ 

#include <avr/io.h>
#include "avr/iom169p.h"
#define MAX_POS 0
#define MIN_POS 5

/**
* Writes a character to the given position on screen.
* @param ch the character that is to be written on screen
* @param pos the position on screen [0,1,...,5]
**/
int write_char(char ch,int pos){
	if(pos >MAX_POS||pos<MIN_POS)
		return -1;
	// The address of the first segment of the display
	uint8_t *first_addr = LCDDR0;
	// The numbers 0-9, credit wikipedia might be wrong
	uint8_t char_arr[] = {0xC3F,0x406,0xDB,0x8F,0xE6,0xED,0xFD,0x1401,0xFF,0xE7};
	
	return 0;
}
int init(void){
	// Setting power options
	CLKPR = 0x80;
	CLKPR = 0X00;
	
	
	
	// Setting the contrast voltage to3.35v and drive time to 300ms
	LCDCCR = LCDCCR&0b11111000;
	// Setting the 
	LCDFRR = LCDFRR&0b10001111;
	
	
	
	
	
	
	
	
	return 1;
}

int main(void)
{
    while (1) 
    {
		
    }
}

