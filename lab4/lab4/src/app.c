/*
 * ui.c
 *
 * Created: 2022-02-22 16:35:29
 *  Author: ivarj
 */ 
#include "../include/app.h"
void change_pulse_gen(app_object * self,uint8_t new_index){
	// sets new pulse gen
	self->current_pulsegen = new_index;
	ASYNC(self,update_display,0);
}
void itterate_freq(app_object * self,int8_t increment){
	// Get current pulse gen
	pulse_gen * current = self->pulse_gens+\
						  self->current_pulsegen;
	uint8_t new_freq = (current->freq+increment);
	// just keep the lowest 2 digits
	new_freq%=100;
	// Message current pulse gen that there is a new freq
	ASYNC(current,change_freq,new_freq);
	ASYNC(self,update_display,0);
}
void save_freq(app_object * self,uint8_t arg){
	// Get the current pulse gen
	pulse_gen * current = self->pulse_gens+\
						  self->current_pulsegen;
	if(current->freq == 0){
		// if we are a 0 we should restore the last stored frequenzy, initiates to 0
		ASYNC(current,change_freq,self->\
			stored_freq[self->current_pulsegen]);
	}
	else{
		// if we are on annything else but 0, set the new freq to 0 and save previous value
		pulse_gen * current = self->pulse_gens+\
					self->current_pulsegen;
		self->stored_freq[self->current_pulsegen] = current->freq;
		ASYNC(current,change_freq,0);
	}
	ASYNC(self,update_display,0);
}
void update_display(app_object * self, int arg){
	// Just to make it a bit prettier
	for(int i = 0; i < self->number_of_pulsegens; i++)
		print_at((self->pulse_gens+i)->freq,4*i,2);
	if(self->current_pulsegen == 0)
		LCDDR0 = LCDDR0^(1<<2);
	else{
		LCDDR2 = LCDDR2^(1<<2);
	}
}
void app_entry(app_object *self,int arg){
		// Runs first time setups that should not be run in the main.c file
		for(int i = 0; i < self->number_of_pulsegens; i++)
			ASYNC((self->pulse_gens+i),pulse,0);
		ASYNC(self,update_display,0);
	
}