/*
 * io.h
 *
 * Created: 2022-02-22 16:15:05
 *  Author: ivarj
 */ 


#ifndef IO_H_
#define IO_H_
#include "TinyTimber.h"
#include <stdint-gcc.h>
#define init_io() {initObject()}
typedef struct{
	Object super;
	} io_object;
volatile void toggle_bit(io_object *self, uint8_t offset);
volatile void set_high(io_object *self,uint8_t offset);
volatile void set_low(io_object *self,uint8_t offset);
volatile uint8_t read_bit_E(io_object *self,uint8_t offset);
volatile uint8_t read_bit_B(io_object *self,uint8_t offset);
#endif /* IO_H_ */