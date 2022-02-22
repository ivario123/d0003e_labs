/*
 * io.c
 *
 * Created: 2022-02-22 16:15:29
 *  Author: ivarj
 */ 
#include "../include/io.h"

void init_io(io_object *self, uint8_t *reg){
	self->super.ownedBy = NULL;
	self->super.wantedBy = NULL;
	self->reg = reg;	
}
void toggle_io_bit(io_object *self,uint8_t bitnmr){
	if (bitnmr >7)
		return;
	*(self->reg) = (*(self->reg)^(1<<bitnmr));
}