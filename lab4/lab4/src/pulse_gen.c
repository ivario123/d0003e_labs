/*
 * pulse_gen.c
 *
 * Created: 2022-02-22 14:27:18
 *  Author: ivarj
 */ 
#include "../include/puls_gen.h"
void init_pulse_gens(pulse_gen * self, uint8_t freq, uint8_t bit_offset,io_object * io_reg){
	// set the first pulsgen
	self->super.ownedBy = NULL;
	self->super.wantedBy = NULL;
	self->freq = freq;
	self->bit_offset = bit_offset;
	self->io_reg =  io_reg;
}
void set_value(pulse_gen *self, uint8_t state){
	AFTER(MSEC(1000/(self->freq)),self,set_value,!state);
	SYNC(self->io_reg,toggle_io_bit,self->bit_offset);
}
// Gets applied in the next cycle
void change_freq(pulse_gen *self,uint8_t freq){
	self->freq = freq;
}




