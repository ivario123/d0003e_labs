/*
 * puls_gen.h
 *
 * Created: 2022-02-22 14:27:05
 *  Author: ivarj
 */ 


#ifndef PULS_GEN_H_
#define PULS_GEN_H_
// Importing needed libs
#include "TinyTimber.h"
#include <avr/io.h>
// Importing needed reactive objects
#include "io.h"
// Defining init
#define init_pulse_gen(freq, bit_offset,reg_handeler) {initObject(),freq,bit_offset,reg_handeler,0}
typedef struct{
	Object super;				// Castable
	uint8_t freq;				// Frequenzy in hz
	uint8_t bit_offset;			// Which bit is responsible for the pin
	io_object *reg_handeler;	// The current reg, defaults to PINE
	Msg last_message;			// The last async call made
	uint8_t running;
}  pulse_gen;
// Disable the pulse gen, by killing latest message
void disable(pulse_gen *self, int arg);
// used to toggle the pulse gen at the specified freq
void pulse(pulse_gen *self, uint8_t arg);
// Updates the pulse gens freq
void change_freq(pulse_gen *self,uint8_t freq);
#endif /* PULS_GEN_H_ */