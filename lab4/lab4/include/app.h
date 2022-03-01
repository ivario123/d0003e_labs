/*
 * ui.h
 *
 * Created: 2022-02-22 16:35:18
 *  Author: ivarj
 */ 


#ifndef APP_H_
#define APP_H_

#include "TinyTimber.h"
#include "puls_gen.h"
#include "lcd_driver.h"
#define init_app(pulsegens,current_pulsegen,number_of_pulsegens) {initObject(),pulsegens,current_pulsegen,number_of_pulsegens,(uint8_t[]){0,0}}
struct App_Object{
	Object super;
	pulse_gen *pulse_gens;
	uint8_t current_pulsegen;
	uint8_t number_of_pulsegens;
	uint8_t stored_freq[2];
	} typedef app_object;
void save_freq(app_object * self,uint8_t arg);
void itterate_freq(app_object * self,int8_t increment);
void change_pulse_gen(app_object * self,uint8_t dirrection);
void app_main_loop(app_object * self, int arg);
void app_entry(app_object *self,int arg);
#endif /* UI_H_ */