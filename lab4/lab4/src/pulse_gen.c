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
	self->running = 0;
	//write_8(&PORTE,0);
	DDRE = DDRE|0b1010000;
	PORTE = PORTE|0b1010000;
	//write_8_field(&PORTE,1,1,6);
}
void pulse(pulse_gen *self, uint8_t arg){
	uint8_t delay = 1000/self->freq;
	AFTER(MSEC(delay),self,pulse,0);
	SYNC(self->io_reg,set_low,self->bit_offset);
	AFTER(MSEC(delay/2),self->io_reg,set_high,self->bit_offset);
	if(self->running != 1)
		self->running = 1;
}
// Gets applied in the next cycle
void change_freq(pulse_gen *self,uint8_t freq){
	self->freq = freq;
}




