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
void init_lcd ();

/**
* Writes a character to the given position on screen.
* @param ch the character that is to be written on screen
* @param pos the position on screen [0,1,...,5]
**/
void write_char(char ch,int pos);

/**
* Writes a whole string to the screen, if it's longer than 6 elements then it will wrap around
* @param char* ch the string that is to be written to screen
* @param first_pos the on which segment the string should be started
* @return 0 if success
**/
void write_string(char* ch, int first_pos);

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
void toggle_led();
/**
* Writes a long to the lcd display
* @param num the number to be displayed
**/
void write_long(long num);


/************************************************************************/
/*					Modified functions for part 4						*/
/************************************************************************/
void toggle_led_2();
void blink_2();
#endif /* LCD_DRIVER_H_ */