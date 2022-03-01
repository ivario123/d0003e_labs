/*
 * puls_gen.h
 *
 * Created: 2022-02-22 14:27:05
 *  Author: ivarj
 */ 


#ifndef PULS_GEN_H_
#define PULS_GEN_H_

#include "TinyTimber.h"
#include "io.h"
#include <avr/io.h>
#define init_pulse_gen(freq, bit_offset,reg_handeler) {initObject(),freq,bit_offset,reg_handeler}
typedef struct{
	Object super;				// Castable
	uint8_t freq;				// Frequenzy in hz
	uint8_t bit_offset;			// Which bit is responsible for the pin
	io_object *reg_handeler;			// The current reg, defaults to PINE
}  pulse_gen;
void set_pulse_high(pulse_gen * self, uint8_t delay);
// used to toggle the pulse gen at the specified freq
void pulse(pulse_gen *self, uint8_t arg);

void change_freq(pulse_gen *self,uint8_t freq);


#endif /* PULS_GEN_H_ */