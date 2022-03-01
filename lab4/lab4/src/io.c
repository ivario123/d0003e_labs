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
	PINE = PINE ^ field;
}
volatile void set_high(io_object *self,uint8_t offset){
	if (offset >7)
		return;
	uint8_t field = 1<<(offset);
	PINE = PINE|(field);
	
}
volatile void set_low(io_object *self,uint8_t offset){
	if (offset >7)
		return;
	uint8_t field = ~(1<<offset);
	PINE = PINE&field;
	
}
volatile uint8_t read_bit_E(io_object *self,uint8_t offset){
	if (offset >7)
	return;
	uint8_t field_mask = 1<<offset;
	uint8_t reg_val = PINE;
	uint8_t field_val = (reg_val&field_mask)>>offset;
	return field_val;
}
volatile uint8_t read_bit_B(io_object *self,uint8_t offset){
	if (offset >7)
	return;
	uint8_t field_mask = 1<<offset;
	uint8_t reg_val = PINB;
	uint8_t field_val = (reg_val&field_mask)>>offset;
	return field_val;
}