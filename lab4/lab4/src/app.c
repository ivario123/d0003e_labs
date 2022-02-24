/*
 * ui.c
 *
 * Created: 2022-02-22 16:35:29
 *  Author: ivarj
 */ 
#include "../include/app.h"
void init_app(app_object * self,pulse_gen *pulse_gens,uint8_t number_of_pulsegens){
	init_lcd();
	self->super.ownedBy = NULL;
	self->super.wantedBy = NULL;
	self->current_pulsegen = 0;
	self->number_of_pulsegens = number_of_pulsegens;
	self->pulse_gens = pulse_gens;
	self->ui_started = 0;
	self->temp_freq[0] = 0;
	self->temp_freq[1] = 0;
	
}
void change_pulse_gen(app_object * self,uint8_t new_index){
	// gets the next pulse gen
	self->current_pulsegen = new_index;
}
void itterate_freq(app_object * self,uint8_t increment){
	self->temp_freq[self->current_pulsegen] += increment;
	self->temp_freq[self->current_pulsegen] %=100; 
}
void commit_freq(app_object * self,uint8_t arg){
	pulse_gen * current = self->pulse_gens+self->current_pulsegen;
	if(self->temp_freq[self->current_pulsegen] == 0){
		// Do 0 stuff
		self->temp_freq[self->current_pulsegen] = current->freq;
	}
	else{
		SYNC(current,change_freq,self->temp_freq[self->current_pulsegen]%100);
		self->temp_freq[self->current_pulsegen] = 0;
	}
}
void update_display(app_object * self, int arg){
		//print_at(arg,0,2);
		print_at(self->temp_freq[0],0,2);
		print_at(self->temp_freq[1],4,2);
		if(self->current_pulsegen == 0)
			write_8_field(&LCDDR0,1,1,2);
		else{
			write_8_field(&LCDDR2,1,1,2);
		}
		AFTER(MSEC(100),self,update_display,arg+1);
}
void app_entry(app_object *self,int arg){
		if((self->pulse_gens+self->current_pulsegen)->running != 1){
			for(int i = 0; i < self->number_of_pulsegens; i++)
				SYNC((self->pulse_gens+i),pulse,0);
		}
		self->ui_started =1;
		ASYNC(self,update_display,0);
		SYNC(self,app_main,0);
	
}
void app_main(app_object * self,int arg){
		AFTER(MSEC(2000),self,app_main,arg+1);
}