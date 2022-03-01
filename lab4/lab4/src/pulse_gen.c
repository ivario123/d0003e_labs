/*
 * pulse_gen.c
 *
 * Created: 2022-02-22 14:27:18
 *  Author: ivarj
 */ 
#include "../include/puls_gen.h"

void pulse(pulse_gen *self, uint8_t arg){
	if(self->freq == 0)
		return;
	uint64_t delay = 1000000/self->freq;
	SYNC(self->reg_handeler,toggle_bit,self->bit_offset);
	self->message = AFTER(USEC(delay/2),self,pulse,0);
}
void set_pulse_low(pulse_gen *self, int arg){
	SYNC(self->reg_handeler,set_low,self->bit_offset);
	
}
void set_pulse_high(pulse_gen * self, uint8_t delay){
	SYNC(self->reg_handeler,set_high,self->bit_offset);
	AFTER(MSEC(delay),self,pulse,delay);
	
}
// Gets applied in the next cycle
void change_freq(pulse_gen *self,uint8_t freq){
	self->freq = freq;
}




