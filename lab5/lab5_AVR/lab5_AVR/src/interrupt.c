/*
 * button.c
 *
 * Created: 2022-02-23 08:33:01
 *  Author: ivarj
 */ 
#include "../include/interrupt.h"
#define cool_delay 500
void left_right_handeler(interrupt_object *self,int arg){
	ASYNC(self->button,handle_joystick,0);
}
void upp_down_press_handeler(interrupt_object *self, int arg){
	uint8_t press;
	read_8_field(&PINB,&press,1,4);
	if(!press||!(self->button->looping))
		ASYNC(self->button,handle_joystick,0);
		
}