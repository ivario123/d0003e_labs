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
#include "dictionary.h"
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


int three_least_significant(long num);

int int_to_str(uint8_t num,char* buffer);

int is_prime(long num);

int primes();
int toggle_led();
#endif /* LCD_DRIVER_H_ */