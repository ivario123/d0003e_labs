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
io_object io = init_io();
pulse_gen pulse_gens[2] = {init_pulse_gen(1, 4,&io),init_pulse_gen(1, 6,&io)};
app_object app = init_app(pulse_gens,0,2);
button_object button = init_button(&app,&io);
void init_outputs(){
	write_8_field(&DDRE,1,1,4);
	write_8_field(&DDRE,1,1,6);
	write_8_field(&PORTE,1,1,4);
	write_8_field(&PORTE,1,1,6);
}
void init_joystick(){
	
	/************************************************************************/
	/* Setting up the joystick												*/
	/************************************************************************/
	// Set all the relevant regs, this is not run as a task so it should be ok to assume that no interrupts can occur
	// Setting pullup enabled for pin b
	write_8_field(&PORTB,3,2,6); // Set portb 6,7 to pullup enabled
	write_8_field(&PORTB,1,1,4); // Set port b 4 to input pullup enabled
	write_8_field(&PORTE,3,2,2); // Set porte 2,3 to pullup enabled
	EIMSK = (1<<PCIE1) | (1<<PCIE0) | EIMSK;
	//write_8_field(&EIMSK,3,2,6); // enable all ext int
	write_8_field(&PCMSK0,3,2,2); // Enable interrupts on PCINT2,3
	write_8_field(&PCMSK1,0b11,2,6); // Enable intrrupts PCINT15,14
	write_8_field(&PCMSK1,1,1,4);
	// int 15,14,12,3,2
	INSTALL(&button,left_right_handeler,IRQ_PCINT0);
	INSTALL(&button,upp_down_press_handeler,IRQ_PCINT1);
}
int main(void)
{
	init_lcd();
	init_outputs();
	init_joystick();
	return TINYTIMBER(&app,app_entry,0);
}

