/*
 * io.h
 *
 * Created: 2022-02-22 16:15:05
 *  Author: ivarj
 */ 


#ifndef IO_H_
#define IO_H_
// Including the needed libs 
#include "TinyTimber.h"
#include <stdint-gcc.h>
// Defining the init function
#define init_io() {initObject()}
typedef struct{
	Object super;
	} io_object;
/**
* Toggles a bit in the register PORTE, field offset by offset
**/
volatile void toggle_bit(io_object *self, uint8_t offset);
/**
* Sets a bit on the register PORTE low, field offset by offset
**/
volatile void set_low(io_object *self,uint8_t offset);
#endif /* IO_H_ */