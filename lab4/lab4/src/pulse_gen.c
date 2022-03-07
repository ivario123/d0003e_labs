/*
 * pulse_gen.c
 *
 * Created: 2022-02-22 14:27:18
 *  Author: ivarj
 */ 
#include "../include/puls_gen.h"

void pulse(pulse_gen *self, uint8_t arg){
	self->running = 1;
	uint64_t delay = 1000000/self->freq;
	SYNC(self->reg_handeler,toggle_bit,self->bit_offset);
	self->last_message = AFTER(USEC(delay/2),self,pulse,0);
}
void disable(pulse_gen *self, int arg){
	ABORT(self->last_message);
	self->running = 0;
	ASYNC(self->reg_handeler,set_low,self->bit_offset);
}
// Gets applied in the next cycle
void change_freq(pulse_gen *self,uint8_t freq){
	self->freq = freq;
	if(freq == 0)
		ASYNC(self,disable,0);
	else if(self->running == 0)
		ASYNC(self,pulse,0);
}




