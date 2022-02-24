/*
 * Lab4.c
 *
 * Created: 2022-02-21 14:33:47
 * Author : ivarj
 */ 

#include <avr/io.h>
#include "../include/TinyTimber.h"
#include "../include/reg_api.h"
#include "../include/puls_gen.h"
#include "../include/app.h"
#include "../include/button.h"
pulse_gen pulse_gens[2];
app_object app;
io_object io;
button_object button;

int main(void)
{
	init_io(&io,(uint8_t *)(0x2c));
	init_pulse_gens(pulse_gens,1,4,&io);
	init_pulse_gens(pulse_gens+1,3,6,&io);
	init_app(&app,pulse_gens,2);
	init_button(&button,&app);
	return TINYTIMBER(&app,app_entry,0);
}

