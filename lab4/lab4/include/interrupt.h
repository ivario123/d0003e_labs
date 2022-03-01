/*
 * button.h
 *
 * Created: 2022-02-23 08:32:47
 *  Author: ivarj
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_
#include "TinyTimber.h"
#include "button.h"
#define init_interrupt(button) {initObject(),button}

typedef struct{
	Object super;
	button_object *button;
	} interrupt_object;
void left_right_handeler(interrupt_object *self,int arg);
void upp_down_press_handeler(interrupt_object *self, int arg);


#endif /* BUTTON_H_ */