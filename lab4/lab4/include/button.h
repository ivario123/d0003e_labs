/*
 * button.h
 *
 * Created: 2022-03-01 16:20:23
 *  Author: ivarj
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_
#include "app.h"
#include "reg_api.h"
#include <stdint-gcc.h>
#define init_button(app) {initObject(),app}

typedef struct{
	Object super;
	app_object *app;
	uint8_t looping;
}	button_object;

void handle_joystick(button_object *self,int arg);
void handle_left_right(button_object * self,int arg);
#endif /* BUTTON_H_ */