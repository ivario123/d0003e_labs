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

// for initializing the receiver and transmitter
#define MYUBRR FOSC/16/BAUD-1
#define BAUD 9600
#define FOSC 1843200	// Clock Speed


void init_reciever_transmitter(unsigned int ubrr){
	/* Setting the baud rate: */
	UBRR0H = (unsigned char) (ubrr >> 8);
	UBRR0L = (unsigned char) ubrr;
	
	/* Enabling the receiver and transmitter: */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	
	/* Setting the frame format (8data, 2stop bit): */
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void USART_transmit(unsigned int data){
	int* udr = 0xC6;
	/* Waiting for empty transmit buffer: */ 
	while (!(UCSR0A & (1 << *udr)));
	
	/* Copying 9th bit to TXB80: */ 
	UCSR0B &= ~(1 << TXB80);
	
	if (data & 0x0100){
		UCSR0B |= (1 << TXB80);
	}
	
	/* Puts data into buffer, sends the data: */ 
	*udr = data;
}
// UDR address: 0xC6, USCRA address: 0xC0
// From UCSRA: bit 7 = RXC, bit 4 = FE, bit 3 = DOR, bit 2 = UPE
unsigned int USART_recieve(void){
	unsigned char status, resh, resl;
	int* udr = 0xC6;
	int* ucsra = 0xC0;
	
	/* Waiting for data to receive: */
	while ( !(UCSR0A & (1 << RXEN0)));
	
	status = UCSR0A;
	resh = UCSR0B;
	resl = *udr;
	
	if (status & (1 << FE)|(1 << DOR)|(1 << UPE)){
		return -1;
	}
	
	resh = (resh >> 1) & 0x01;
	return ((resh << 8) | resl);
	
}

void main(void)
{
	init_lcd();
	init_reciever_transmitter(MYUBRR);
	// Launching tiny timber, with the app_entry function
	//return TINYTIMBER(&app,app_entry,0);
}

