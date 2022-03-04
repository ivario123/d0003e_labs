/*
 * reg_api.h
 * 
 * This file defines a safe to use register API that correctly modifies field
 * Making bit operations less prone to user errors
 * 
 * Created: 2022-02-22 11:32:35
 *  Author: ivarj
 */ 
// Include guard
#ifndef REG_API_H
#define REG_API_H
// Include needed libs
#include <stdint-gcc.h>
/**
* Reads a u8 from 
**/
inline void read_8(uint8_t *reg, uint8_t *ret){
	*ret = *reg;
}
inline void read_16(uint8_t *reg, uint16_t *ret){
	return;
};
inline void write_8(uint8_t *reg, uint8_t val){
	*reg = val;
}
inline void write_16(uint8_t *reg, uint16_t val){
	return;
}
/**
* In practice it is a modify function, but write seems more appropriate for my use case
**/
inline void write_8_field(volatile uint8_t *reg,uint8_t value, uint8_t field_width,uint8_t offset){
	uint8_t temp;
	read_8(reg,&temp);
	// Masks out the relevant bits
	uint8_t mask = ((1<<field_width)-1)<<offset;
	value = ((~(mask))&temp)| (value<<offset&mask);
	write_8(reg,value);
}
/**
* Reads a field from an address. 
**/
inline void read_8_field(volatile uint8_t *reg, uint8_t* ret, uint8_t field_width,uint8_t offset){
	uint8_t temp;
	read_8(reg,&temp);
	// Masks out the relevant bits
	uint8_t mask = ((1<<field_width)-1)<<offset;
	*ret = (temp&mask)>>offset;
}

#endif