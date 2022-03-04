/*
 * Lab4.c
 *
 * Created: 2022-02-21 14:33:47
 * Author : ivarj
 */ 
// Importing the libraries that we need to initiate
#include <avr/io.h>
#include "../include/TinyTimber.h"
#include "../include/reg_api.h"
#include "../include/lcd_driver.h"

// Import object definitions
#include "../include/puls_gen.h"
#include "../include/app.h"
#include "../include/button.h"
#include "../include/interrupt.h"

// Instantiate all of the objects using macros
io_object io = init_io();
pulse_gen pulse_gens[2] = {init_pulse_gen(1, 4,&io),init_pulse_gen(2, 6,&io)};
app_object app = init_app(pulse_gens,0,2);
button_object button = init_button(&app);
interrupt_object interrupts = init_interrupt(&button);

// Init functions allowing us to run the setup for buttons
void init_outputs(){
	write_8_field(&DDRE,1,1,4);
	write_8_field(&DDRE,1,1,6);
}
void init_joystick(){
	
	/************************************************************************/
	/* Setting up the joystick												*/
	/************************************************************************/
	write_8_field(&PORTB,3,2,6); // Set portb 6,7 to pullup enabled
	write_8_field(&PORTB,1,1,4); // Set port b 4 to input pullup enabled
	write_8_field(&PORTE,3,2,2); // Set porte 2,3 to pullup enabled
	write_8_field(&EIMSK,3,2,6); // Enable all external interrupt registers
	write_8_field(&PCMSK0,3,2,2); // Enable interrupts on PCINT2,3
	write_8_field(&PCMSK1,3,2,6); // Enable interrupts PCINT15,14
	write_8_field(&PCMSK1,1,1,4); // Enable interrupts for PCINT12
	// Installing handelers for the relevabt actions
	INSTALL(&interrupts,left_right_handeler,IRQ_PCINT0);	
	INSTALL(&interrupts,upp_down_press_handeler,IRQ_PCINT1);
}
int main(void)
{
	init_lcd();
	init_outputs();
	init_joystick();
	// Launching tiny timber, with the app_entry function
	return TINYTIMBER(&app,app_entry,0);
}

