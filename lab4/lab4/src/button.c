/*
 * button.c
 *
 * Created: 2022-03-01 16:20:33
 *  Author: ivarj
 */
#include "../include/button.h"
void handle_joystick(button_object *self,int arg){
	self->looping = 1;
	uint8_t up,down,press,left,right;
	// Read the pin values, using an inlined function
	read_8_field(&PINB,&press,1,4);
	read_8_field(&PINB,&up,1,6);
	read_8_field(&PINB,&down,1,7);
	read_8_field(&PINE,&left,1,2);
	read_8_field(&PINE,&right,1,3);
	if((up)&&(down)){
		self->looping = 0;
	}
	// If not exactly one of the buttons have been pressed return
	// This makes it not act on release
	if(up+down+press+left+right != 4&& arg == 1){
		self->looping = 0;
		return;
	}
	else if(up+down+press+left+right != 4)
	return;
	else 
	// Treating it like booleans, all but 0 is 1 thus if !val is true, reg is 0,
	// Just think it looks neater than ==0
	if(!up)
		ASYNC(self->app,itterate_freq,1);
	else if(!down)
		ASYNC(self->app,itterate_freq,-1);
	else if(!press)
		ASYNC(self->app,save_freq,0);
	else if(!right)
		ASYNC(self->app,change_pulse_gen,1);
	else if(!left)
		ASYNC(self->app,change_pulse_gen,0);
		
		
	if((!up)||(!down)){
		AFTER(MSEC(150),self,handle_joystick,1);
	}
	else if(arg == 1){
		self->looping = 0;
	}
}