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
	write_8_field(&PORTB,1,1,4); // Set port b 4 to input pullup enabled
	write_8_field(&PORTE,3,2,2); // Set porte 2,3 to pullup enabled
	EIMSK = (1<<PCIE1) | (1<<PCIE0) | EIMSK;
	//write_8_field(&EIMSK,3,2,6); // enable all ext int
	write_8_field(&PCMSK0,3,2,2); // Enable interrupts on PCINT2,3
	write_8_field(&PCMSK1,0b11,2,6); // Enable intrrupts PCINT15,14
	write_8_field(&PCMSK1,1,1,4);
	
	// int 15,14,12,3,2
	
	INSTALL(self,left_right_handeler,IRQ_PCINT0);
	INSTALL(self,upp_down_press_handeler,IRQ_PCINT1);
	self->super.ownedBy = NULL;
	self->super.wantedBy = NULL;
	self->app = app;
	//INSTALL(self,upp_handeler)
}
// pin B is down
// pin c is up
// DOWN is down
// pin a is right
// pin d is left
// pin A and B and DOWN are port b 6 and 7 4
// pin C and D are port e 2 and 3 
// Handles left, right
volatile void left_right_handeler(button_object *self,int arg){
	volatile uint8_t left,right;
	read_8_field(&PINE,&left,1,2);
	read_8_field(&PINE,&right,1,3);
	if(right == 0){
		SYNC(self->app,change_pulse_gen,1);
	}
	else if(left == 0){
		SYNC(self->app,change_pulse_gen,0);
	}
	
}
// pin B is down
// pin c is up
// DOWN is press
// pin a is right
// pin d is left
// pin A and B and DOWN are port b 6 and 7 4
// pin C and D are port e 2 and 3 
// Handles up, down, and press
volatile void upp_down_press_handeler(button_object *self, int arg){
	volatile uint8_t up,down,press;
	read_8_field(&PINB,&press,1,4);
	read_8_field(&PINB,&down,1,7);
	read_8_field(&PINB,&up,1,6);
	if(up == 0)
		ASYNC(self->app,itterate_freq,1);
	else if(down == 0)
		ASYNC(self->app,itterate_freq,-1);
	else if(press == 0){
		SYNC(self->app,commit_freq,0);
	}
	
	if(up == 0 || down == 0 ){
		AFTER(MSEC(cool_delay),self,upp_down_press_handeler,arg);
	}
	
	
}