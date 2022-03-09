/*
 * io.c
 *
 * Created: 2022-02-22 16:15:29
 *  Author: ivarj
 */ 
#include "../include/io.h"
#include <avr/io.h>
volatile void toggle_bit(io_object *self, uint8_t offset){
	if(offset > 7)
		return;
	uint8_t field = 1<<(offset);
	PORTE = PORTE ^ field;
}
volatile void set_low(io_object *self,uint8_t offset){
	if (offset >7)
		return;
	uint8_t field = ~(1<<offset);
	PORTE = PORTE&field;
	
}