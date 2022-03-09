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
#include "../include/app.h"
#include "../include/button.h"
#include "../include/interrupt.h"

// for initializing the receiver and transmitter
#define MYUBRR FOSC/16/BAUD-1
#define BAUD 9600
#define FOSC 1843200	// Clock Speed


void init_reciever_transmitter(unsigned int ubrr){
	/* Setting the baud rate: */
	UBRR0H = (unsigned char) (ubrr >> 8);
	UBRR0L = (unsigned char) ubrr;
	
	/* Enabling the reciever and transmitter: */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	
	/* Setting the frame format (8data, 2stop bit): */
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

int main(void)
{
	init_lcd();
	init_reciever_transmitter(MYUBRR);
	// Launching tiny timber, with the app_entry function
	return TINYTIMBER(&app,app_entry,0);
}

