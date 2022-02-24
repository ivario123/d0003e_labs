/*
 * button.c
 *
 * Created: 2022-02-23 08:33:01
 *  Author: ivarj
 */ 
// pin B is down
// pin c is up
// pin a is right
// pin d is left
// pin A and B are port b 6 and 7
// pin C and D are port e 2 and 3 
// Two interrupt handelers, 
#include "../include/button.h"
void init_button(button_object *self, app_object *app){
	// Set all the relevant regs, this is not run as a task so it should be ok to assume that no interrupts can occur
	// Setting pullup enabled for pin b
	write_8_field(&PORTB,3,2,6); // Set portb 6,7 to pullup enabled
	write_8_field(&PORTE,3,2,2); // Set porte 2,3 to pullup enabled
	EIMSK = (1<<PCIE1) | (1<<PCIE0) | EIMSK;
	//write_8_field(&EIMSK,3,2,6); // enable all ext int
	write_8_field(&PCMSK0,3,2,2); // Enable interrupts on PCINT2,3
	write_8_field(&PCMSK1,3,2,6); // Enable intrrupts PCINT15,14
	
	INSTALL(self,upp_handeler,IRQ_PCINT0);
	INSTALL(self,upp_handeler,IRQ_PCINT1);
	self->super.ownedBy = NULL;
	self->super.wantedBy = NULL;
	self->app = app;
	//INSTALL(self,upp_handeler)
}
// Handles left, right

// Handles up_down
void upp_handeler(button_object *self, int arg){
		// Check that the button is being held
		ASYNC(self->app,itterate_freq,1);
		//uint8_t delay = 10;
		//AFTER(MSEC(delay),self,upp_handeler,0)
}
void down_handeler(button_object *self,int arg){
		// Check that the button is being held
		ASYNC(self->app,itterate_freq,1);
		
		
		//uint8_t delay = 10;
		//AFTER(MSEC(delay),self,down_handeler,0)
	
}
void right_handeler(button_object *self,int arg){
	SYNC(self->app,itterate_pulse_gen,1);
	
	
	uint8_t delay = 10;
	//AFTER(MSEC(delay),self,right_handeler,0);
	
}
void left_handeler(button_object *self,int arg){
	
	SYNC(self->app,itterate_pulse_gen,-1);
	
	
	uint8_t delay = 10;
	//AFTER(MSEC(delay),self,left_handeler,0);
}