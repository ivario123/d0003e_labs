/*
 * button.c
 *
 * Created: 2022-03-01 16:20:33
 *  Author: ivarj
 */
#include "../include/button.h"
void handle_joystick(button_object *self,int arg){
	uint8_t up,down,press,left,right;
	read_8_field(&PINB,&press,1,4);
	read_8_field(&PINB,&up,1,6);
	read_8_field(&PINB,&down,1,7);
	read_8_field(&PINE,&left,1,2);
	read_8_field(&PINE,&right,1,3);
	
	if(up+down+press+left+right != 4)
	return;

	if(up == 0)
		ASYNC(self->app,itterate_freq,1);
	else if(down == 0)
		ASYNC(self->app,itterate_freq,-1);
	else if(press == 0)
		ASYNC(self->app,save_freq,0);
	else if(right == 0)
		ASYNC(self->app,change_pulse_gen,1);
	else if(left == 0)
		ASYNC(self->app,change_pulse_gen,0);

	AFTER(MSEC(250),self,handle_joystick,arg);
}