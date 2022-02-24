/*
 * puls_gen.h
 *
 * Created: 2022-02-22 14:27:05
 *  Author: ivarj
 */ 


#ifndef PULS_GEN_H_
#define PULS_GEN_H_

#include "TinyTimber.h"
#include "reg_api.h"
#include "io.h"
#include <avr/io.h>

typedef struct{
	Object super;				// Castable
	uint8_t freq;				// Frequenzy in hz
	uint8_t bit_offset;			// Which bit is responsible for the pin
	io_object *io_reg;			// The current reg, defaults to PINE
	uint8_t running;
}  pulse_gen;

void init_pulse_gens(pulse_gen * self, uint8_t freq, uint8_t bit_offset,io_object * io_reg);
// used to toggle the pulse gen at the specified freq
void pulse(pulse_gen *self, uint8_t arg);

void change_freq(pulse_gen *self,uint8_t freq);


#endif /* PULS_GEN_H_ */