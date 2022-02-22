/*
 * ui.h
 *
 * Created: 2022-02-22 16:35:18
 *  Author: ivarj
 */ 


#ifndef APP_H_
#define APP_H_

#include "TinyTimber.h"
#include "lcd_driver.h"
#include "puls_gen.h"
typedef struct{
	Object super;
	pulse_gen pulse_gens*;
	uint8_t current_pulsegen;
	uint8_t number_of_pulsegens;
	} app_object;

void next_pulse_gen;
void set_freq;
void update_display;

#endif /* UI_H_ */