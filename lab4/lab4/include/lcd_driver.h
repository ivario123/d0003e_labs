#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_
// Relevant defines
#define MIN_POS 0
#define MAX_POS 5
// Importing needed libs
#include "string.h"
#include "reg_api.h"
#include <stdint-gcc.h>
#include <avr/io.h>
/**
* Initiates the lcd screen with predefined parameters
* @param ch the character that is to be written on screen
* @param pos the position on screen [0,1,...,5]
**/
void init_lcd (void);
/**
* Prints a number of width digits starting at position
* pos
**/
void print_at(uint8_t num, uint8_t pos, uint8_t width);
/**
* Writes a character to the given position on screen.
* @param ch the character that is to be written on screen
* @param pos the position on screen [0,1,...,5]
**/
void write_char(char ch,int pos);
#endif /* LCD_DRIVER_H_ */