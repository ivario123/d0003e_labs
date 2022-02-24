/*
 * button.h
 *
 * Created: 2022-02-23 08:32:47
 *  Author: ivarj
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_
#define cool_delay 250
#include "TinyTimber.h"
#include "app.h"
#include "reg_api.h"
#include <stdint-gcc.h>

typedef struct{
	Object super;
	app_object *app;
	} button_object;
void init_button(button_object *self, app_object *app);
void left_right_handeler(button_object *self,int arg);
void upp_down_press_handeler(button_object *self, int arg);


#endif /* BUTTON_H_ */