/*
 * ui.h
 *
 * Created: 2022-02-22 16:35:18
 *  Author: ivarj
 */ 


#ifndef APP_H_
#define APP_H_
// Includes needed libraries
#include "TinyTimber.h"
#include "lcd_driver.h"

// Includes the needed reactive objects
#include "puls_gen.h"

#define init_app(pulsegens,current_pulsegen,number_of_pulsegens) {initObject(),pulsegens,current_pulsegen,number_of_pulsegens,(uint8_t[]){0,0}}
struct App_Object{
	Object super;
	pulse_gen *pulse_gens;
	uint8_t current_pulsegen;
	uint8_t number_of_pulsegens;
	uint8_t stored_freq[2];
	} typedef app_object;
/**
* Saves the current frequency and acts
* depending on the current freq
**/
void save_freq(app_object * self,uint8_t arg);
/**
* Increments the current pulse gens frequenzy
* This is a middle man for the button interrupt and 
* The pulse gens
**/
void itterate_freq(app_object * self,int8_t increment);
/**
* Changes to the new_index pulse gen, used with index 0,1
**/
void change_pulse_gen(app_object * self,uint8_t new_index);
/**
* Updates the display, showing the new data
**/
void update_display(app_object * self, int arg);
/**
* Running 3 first setup things, that I don't think belongs to the main.c
**/
void app_entry(app_object *self,int arg);
#endif /* UI_H_ */