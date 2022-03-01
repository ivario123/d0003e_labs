/*
 * ui.c
 *
 * Created: 2022-02-22 16:35:29
 *  Author: ivarj
 */ 
#include "../include/app.h"
void change_pulse_gen(app_object * self,uint8_t new_index){
	// gets the next pulse gen
	self->current_pulsegen = new_index;
	ASYNC(self,update_display,0);
}
void itterate_freq(app_object * self,int8_t increment){
	pulse_gen * current = self->pulse_gens+self->current_pulsegen;
	current->freq=(current->freq+increment)%100;
	if((current->freq+increment)%100 ==0){
		ABORT(current->message);
		ASYNC(current,set_pulse_low,0);
	}
	ASYNC(self,update_display,0);
}
void save_freq(app_object * self,uint8_t arg){
	pulse_gen * current = self->pulse_gens+self->current_pulsegen;
	if(current->freq == 0){
		current->freq = self->stored_freq[self->current_pulsegen];
		ASYNC(current,pulse,0);
	}
	else{
		pulse_gen * current = self->pulse_gens+self->current_pulsegen;
		self->stored_freq[self->current_pulsegen] = current->freq;
		current->freq=0; 
		ABORT(current->message);
		ASYNC(current,set_pulse_low,0);
	}
	ASYNC(self,update_display,0);
}
void update_display(app_object * self, int arg){
		print_at((self->pulse_gens)->freq,0,2);
		print_at((self->pulse_gens+1)->freq,4,2);
		if(self->current_pulsegen == 0)
			LCDDR0 = LCDDR0^(1<<2);
		else{
			LCDDR2 = LCDDR2^(1<<2);
		}
}
void app_entry(app_object *self,int arg){
		for(int i = 0; i < self->number_of_pulsegens; i++)
			ASYNC((self->pulse_gens+i),pulse,0);
		ASYNC(self,update_display,0);
	
}