/*
 * lcd_driver.c
 *
 * Created: 2022-01-21 08:21:07
 *  Author: ivarj
 */ 

#include "../include/lcd_driver.h"
#define CLOCK_SPEED 8000000  				// The clock speed in Hz
#define REFRESH_RATE 31250					// A second measured in bits of the timer register
long dict_arr[] = {
	0x1551,
	0x0110,
	0x1E11,
	0x1B11,
	0x0B50,
	0x1B41,
	0x1F41,
	0x0111,
	0x1F51,
	0x1B51
};
int write_char(char ch,int pos){
	
	// The address of the first segment of the display
	
	
	
	
	LCDDR0 = dict_arr[0];
	
	return success;
	
	
}
int write_long(long num){
	char buffer[7];
	num = six_least_significant(num);
	int_to_str(num,buffer);
	
}
int write_string(char* ch, int first_pos){
	first_pos = first_pos%MAX_POS;
	while(*ch != '\0'){
		write_char(*ch,first_pos);
		first_pos++;
		first_pos = first_pos%MAX_POS;
		ch++;
	}
	return success;
}
/************************************************************************/
/* This function could be shortend significantly,       */
/* I do however feel that this is its most readable form*/
/************************************************************************/
int init_lcd(){
		
		
		//-----------------------------------
		// Status manipulation
		//-----------------------------------
		
		// enabling the lcd
		LCDCRA = LCDCRA|(1<<LCDEN);
		// Setting low power wave form
		LCDCRA = LCDCRA|(1<<LCDAB);
		// disabling the interrupt
		LCDCRA = LCDCRA&(~(1<<LCDIF));
		// Disabling blanking
		LCDCRA = LCDCRA&(~(1));
		
		
		//-----------------------------------
		// Clock manipulation
		//-----------------------------------
		
		// setting the clock source to external
		LCDCRB = LCDCRB|(1<<LCDCS);
		// Setting Bias
		LCDCRB = LCDCRB&(~(1<<LCD2B));
		// Setting duty cycle
		LCDCRB = LCDCRB|((3<<LCDMUX0));
		// Setting number of active segments to 25
		LCDCRB = LCDCRB|(7);
		
		
		//-----------------------------------
		// Frame rate manipulation
		//-----------------------------------
		// Set n = 16
		LCDFRR = LCDFRR&(~(7<<LCDPS0));
		// Set D = 8
		LCDFRR = LCDFRR|(7);
		
		
		//-----------------------------------
		// Contrast manipulation
		//-----------------------------------
		// Setting msb->msb-2 to 0 to set drive time to 300 us
		LCDCCR = LCDCCR&(~(7<< LCDDC0));
		// Setting lsb -> lsb+3 to 1 to set voltage to 3.35V 
		LCDCCR = LCDCCR|((15));
		
		return success;
}





int is_prime(long num){
	
	// base cases 0-3
	if (num <= 3)
		return 1;
	// base case num is even
	if(num%2 == 0)
		return 0;
	// Start on 3
	uint8_t counter = 3;
	// Only check odd numbers up to half of num
	while(counter <num/2){
		if(num%counter == 0)
			return 0;
		counter+=2;
	}
	return 1;
}

int primes(){
	long num = 1;
	while(1)
	{
		if(num >= 3){
			if (num%2 == 0)
				num++;
			else
				num +=2;	
		}
		else 
			num++;
		if(is_prime(num)==1){
			uint8_t temp = three_least_significant(num);
		
		
			char buffer[10];
			int_to_str(temp,buffer);
			write_string(buffer,0);
		}
		// Print string to screen
	}
	return 0;
}

int toggle_led(){
	if((LCDDR0^2)== 0)
		LCDDR0=0;
	else
		LCDDR0=2;
	return 0;
}
int blink(){
	uint16_t freq = 31250/2;		// The segment should turn on and of every half cycle i.e flicker with 2 Hz frequenzy
	uint16_t last_time = TCNT1;
	// uint16t's wrap around in the same way for timer and normal addition
	while(1){
		while(((uint16_t)TCNT1)< last_time+freq);
		last_time =(uint16_t)TCNT1;
		toggle_led();
	}
	return 0;
}

