/*
 * io.c
 *
 * Created: 2022-02-22 16:15:29
 *  Author: ivarj
 */ 
#include "../include/io.h"
#include <avr/io.h>
void init_io(io_object *self, uint8_t *reg){
	self->super.ownedBy = NULL;
	self->super.wantedBy = NULL;
	self->reg = reg;	
}
void toggle_io_bit(io_object *self,uint8_t offset){
	if (offset >7)
		return;
	write_8_field(&PINE,1,1,offset);
	
}
void set_high(io_object *self,uint8_t offset){
	if (offset >7)
		return;
	PINE = PINE|(1<<offset);
	
}
void set_low(io_object *self,uint8_t offset){
	if (offset >7)
		return;
	PINE = PINE&(~(1<<offset));
	
}