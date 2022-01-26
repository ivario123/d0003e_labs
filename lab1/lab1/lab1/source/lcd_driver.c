/*
 * lcd_driver.c
 *
 * Created: 2022-01-21 08:21:07
 *  Author: ivarj
 */ 

// Notes
// 0x78 seems to controll lower segment of segment 5
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
	if(pos < 0 || pos > 5)
		return 0;
	// Predefine num
	uint16_t num = 0x0;
	uint8_t *first_address = (uint8_t *)0xEC;
	volatile uint8_t *address = first_address+(pos>>1);
	// Clear the segment
	// Set num to a value if exists in array
	if(ch>=48&& ch<=57){
		num = dict_arr[ch-48];
	}
	
	
	for( int i= 0; i < 4; i++){
		// Always grab the lowest 4 bits of the char as nibble 
		uint8_t nibble = num&0xf;
		num>>=4;	
		
		
		if(pos%2==0)
		{
			*address = (*address)&0xf0;
			*address = (*address)|nibble;
			// Write the data to the lower bits
		}
		else
		{
			*address = (*address)&0x0f;
			*address =  *address | nibble << 4;
			// Write the data to the higher bits
		}
		address+=5;
		
	}
	return success;
	
	
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


void writeLong(long num){
	int temp;
	six_least_significant(num,&temp);
	char buffer[10];
	int_to_str(temp,buffer);
	write_string(buffer,0);
}


int is_prime(long num){
	
	// base cases 0-3
	if (num <= 3)
		return 1;
	// base case num is even
	if(num%2 == 0)
		return 0;
	// Start on 3
	long counter = 3;
	// Only check numbers up to half of num
	while(counter <num/2){
		if(num%counter == 0)
			return 0;
		counter++;
	}
	return 1;
}

void primes(){
	// Simply generates primes
	long num = 0;
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
			writeLong(num);
		}
		// Print string to screen
	}
}

int toggle_led(){
	// If the segment is on turn it of
	if((LCDDR0&2)>>1== 0)
		LCDDR0 = LCDDR0|2;
	// Else turn it on
	else
		LCDDR0= LCDDR0^2;
	return 0;
}
int blink(){
	uint16_t freq = 31250/2;		// The segment should turn on and of every half cycle i.e. flicker with 2 Hz frequency
	uint16_t last_time = TCNT1;
	// uint16t's wrap around in the same way for timer and normal addition
	while(1){
		while(((uint16_t)TCNT1)!= last_time+freq);
		last_time =(uint16_t)TCNT1;
		toggle_led();
	}
	return 0;
}

















int toggle_led_2(){
	if((LCDDR8&1)== 0)
	LCDDR8 = LCDDR8|1;
	else
	LCDDR8= LCDDR8^1;
	return 0;
}


int blink_2(){
	
	if((LCDDR8&1)== 0)
	LCDDR8 = LCDDR8|2;
	else
	LCDDR8= LCDDR8^2;
	return 0;
}

int write_char_2(char ch, int pos){
	if(pos < 0 || pos > 5)
	return 0;
	// Predefine num
	uint16_t num = 0x0;
	uint8_t *first_address = (uint8_t *)0xEC;
	volatile uint8_t *address = first_address+(pos>>1);
	// Clear the segment
	// Set num to a value if exists in array
	if(ch>=48&& ch<=57){
		num = dict_arr[ch-48];
	}
	
	
	for( int i= 0; i < 4; i++){
		// Always grab the lowest 4 bits of the char as nibble
		uint8_t nibble = num&0xf;
		num>>=4;
		
		
		if(pos%2==0)
		{
			*address = (*address)&(0xf0);
			*address = (*address)|nibble;
			// Write the data to the lower bits
		}
		else
		{
			*address = (*address)&(0x0f);
			*address =  *address | (nibble << 4);
			// Write the data to the higher bits
		}
		address+=5;
		
	}
	return success;
}



int write_string_2(char * ch, int first_pos){
	first_pos = first_pos%MAX_POS;
	while(*ch != '\0'){
		write_char_2(*ch,first_pos);
		first_pos++;
		first_pos = first_pos%MAX_POS;
		ch++;
	}
	return success;
}




void writeLong_2(long num){
	int temp;
	six_least_significant(num,&temp);
	char buffer[10];
	int_to_str(temp,buffer);
	write_string_2(buffer,0);
}




