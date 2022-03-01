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
#include "io.h"
#include <stdint-gcc.h>
#define init_button(app,io) {initObject(),app,io}

typedef struct{
	Object super;
	app_object *app;
	io_object *io;
	} button_object;
void left_right_handeler(button_object *self,int arg);
void upp_down_press_handeler(button_object *self, int arg);


#endif /* BUTTON_H_ */