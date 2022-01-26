/*
 * lcd_driver.h
 *
 * Created: 2022-01-21 08:20:55
 *  Author: ivarj
 */ 


#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_


#define MIN_POS 0
#define MAX_POS 5
#include "string.h"
#include <stdint-gcc.h>
#include <avr/io.h>
enum ERROR{
	success = 0,
	startup = 1,
	writechar = 1
	};



/**
* Initiates the lcd screen with predefined parameters
* @param ch the character that is to be written on screen
* @param pos the position on screen [0,1,...,5]
**/
int init_lcd ();

/**
* Writes a character to the given position on screen.
* @param ch the character that is to be written on screen
* @param pos the position on screen [0,1,...,5]
**/
int write_char(char ch,int pos);

/**
* Writes a whole string to the screen, if it's longer than 6 elements then it will wrap around
* @param char* ch the string that is to be written to screen
* @param first_pos the on which segment the string should be started 
* @return 0 if success
**/
int write_string(char* ch, int first_pos);

/**
* Checks if a number is a prime number
* @param num the number the user wants to check
* @return 1 if it is, 0 if not
**/
int is_prime(long num);

/**
* Loops for ever while generating new prime numbers
*/
void primes();
/**
* Toggles a segment on the display
**/
int toggle_led();
/**
* Writes a long to the lcd display
* @param num the number to be displayed
**/
void writeLong(long num);


/************************************************************************/
/*					Modified functions for part 4						*/
/************************************************************************/
int toggle_led_2();
int blink_2();
int write_char_2(char ch, int pos);
int write_string_2(char * ch, int first_pos);
void writeLong_2(long num);
#endif /* LCD_DRIVER_H_ */