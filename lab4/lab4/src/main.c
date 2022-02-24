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
inline void init(){
	// Set pine to output
	write_8(&PORTE,0);
	write_8_field(&PORTE,1,1,6);
}

int main(void)
{
	init();
	init_io(&io,&PINE);
	// Init the pulse gens
	init_pulse_gens(pulse_gens,1,4,&io);
	init_pulse_gens(pulse_gens+1,2,6,&io);
	init_app(&app,pulse_gens,1);
	init_button(&button,&app);
	//SYNC(&app,update_display,0);
	//SYNC(pulse_gens,set_value,0);
	return TINYTIMBER(&app,app_main,0);
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

