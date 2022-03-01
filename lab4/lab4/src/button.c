/*
 * button.c
 *
 * Created: 2022-02-23 08:33:01
 *  Author: ivarj
 */ 
#include "../include/button.h"
#define cool_delay 500
void left_right_handeler(button_object *self,int arg){
	volatile uint8_t left,right;
	left = SYNC(self->io,read_bit_E,2);
	right = SYNC(self->io, read_bit_E,3);
	if(right +left != 1)
		return;
	if(right == 0){
		ASYNC(self->app,change_pulse_gen,1);
	}
	else if(left == 0){
		ASYNC(self->app,change_pulse_gen,0);
	}
	
	
}
void upp_down_press_handeler(button_object *self, int arg){
	volatile uint8_t up,down,press;
	press = SYNC(self->io,read_bit_B,4);
	down = SYNC(self->io, read_bit_B,7);
	up = SYNC(self->io, read_bit_B,6);
	if(up+down+press != 2)
		return;

	if(up == 0)
		ASYNC(self->app,itterate_freq,1);
	else if(down == 0)
		ASYNC(self->app,itterate_freq,-1);
	else if(press == 0){
		ASYNC(self->app,save_freq,0);
	}
	else
		return;
	AFTER(MSEC(cool_delay),self,upp_down_press_handeler,arg);
	
}