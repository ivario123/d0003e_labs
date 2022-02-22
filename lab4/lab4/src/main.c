/*
 * Lab4.c
 *
 * Created: 2022-02-21 14:33:47
 * Author : ivarj
 */ 

#include <avr/io.h>
#include "../include/TinyTimber.h"
#include "../include/lcd_driver.h"
#include "../include/reg_api.h"
#include "../include/puls_gen.h"
 

pulse_gen pulse_gens[2];
io_object io;
inline void init(){
	// Set pine to output
	write_8(PORTE,0);
	write_8_field(PORTE,1,1,6);
}

int main(void)
{
	init_lcd();
	print_at(12,0,2);
	init_io(&io,&PINE);
	// Init the pulse gens
	init_pulse_gens(pulse_gens,1,4,&io);
	init_pulse_gens(pulse_gens+1,2,6,&io);
	//SYNC(pulse_gens,set_value,0);
	ASYNC(pulse_gens+1,set_value,0);
	return TINYTIMBER(pulse_gens,set_value,0);
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

