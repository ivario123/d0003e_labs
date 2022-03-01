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
	return;
}
void itterate_freq(app_object * self,int8_t increment){
	pulse_gen * current = self->pulse_gens+self->current_pulsegen;
	current->freq+=increment; 
}
void save_freq(app_object * self,uint8_t arg){
	pulse_gen * current = self->pulse_gens+self->current_pulsegen;
	if(current->freq == 0){
		current->freq = self->stored_freq[self->current_pulsegen];
	}
	else{
		self->stored_freq[self->current_pulsegen] = current->freq;
	}
}
void app_main_loop(app_object * self, int arg){
		print_at((self->pulse_gens)->freq,0,2);
		print_at((self->pulse_gens+1)->freq,4,2);
		if(self->current_pulsegen == 0)
			LCDDR0 = LCDDR0^(1<<2);
		else{
			LCDDR2 = LCDDR2^(1<<2);
		}
		AFTER(MSEC(10),self,app_main_loop,0);
}
void app_entry(app_object *self,int arg){
		for(int i = 0; i < self->number_of_pulsegens; i++)
			ASYNC((self->pulse_gens+i),pulse,0);
		ASYNC(self,app_main_loop,0);
	
}