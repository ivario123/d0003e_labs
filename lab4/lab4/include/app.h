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
struct App_Object{
	Object super;
	pulse_gen *pulse_gens;
	uint8_t current_pulsegen;
	uint8_t number_of_pulsegens;
	uint8_t ui_started;
	uint8_t temp_freq[2];
	} typedef app_object;
void commit_freq(app_object * self,uint8_t arg);
void itterate_freq(app_object * self,uint8_t increment);
void init_app(app_object * self,pulse_gen *pulse_gens,uint8_t number_of_pulsegens);
void change_pulse_gen(app_object * self,uint8_t dirrection);
void update_display(app_object * self, int arg);
void app_main(app_object * self,int arg);
void app_entry(app_object *self,int arg);
#endif /* UI_H_ */