/*
 * button.h
 *
 * Created: 2022-02-23 08:32:47
 *  Author: ivarj
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "TinyTimber.h"
#include "app.h"
#include "reg_api.h"
#include <stdint-gcc.h>

typedef struct{
	Object super;
	app_object *app;
	} button_object;
void init_button(button_object *self, app_object *app);
void upp_handeler(button_object *self, int arg);
void down_handeler(button_object *self,int arg);
void right_handeler(button_object *self,int arg);
void left_handeler(button_object *self,int arg);


#endif /* BUTTON_H_ */