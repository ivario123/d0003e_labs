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
typedef struct{
	Object super;
	uint8_t * reg;
	} io_object;
void init_io(io_object *self, uint8_t *reg);
void toggle_io_bit(io_object *self,uint8_t bitnmr);


#endif /* IO_H_ */