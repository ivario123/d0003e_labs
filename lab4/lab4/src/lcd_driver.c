#include "../include/lcd_driver.h"
#include <avr/interrupt.h>
#define CLOCK_SPEED 8000000  				// The clock speed in Hz
#define REFRESH_RATE 31250					// A second measured in bits of the timer register




// Our dictionary
long dict_arr[] = {
	0x1551,				// Represents 0
	0x0110,				// Represents 1
	0x1E11,				// ...		  2
	0x1B11,				// ...		  3
	0x0B50,				// ...		  4
	0x1B41,				// ...		  5
	0x1F41,				// ...		  6
	0x0111,				// ...		  7
	0x1F51,				// ...		  8
	0x1B51				// ...		  9
};



/************************************************************************/
/*								TASK 1									*/
/************************************************************************/
inline void init_lcd(void){
	// Using inlined accesses makes the optimization much more agressive
	// it results in a much more efficiant implemantation
	//-----------------------------------
	// Status manipulation
	//-----------------------------------
	
	// enabling the lcd
	
	write_8_field(&LCDCRA,1,1,LCDEN);
	//LCDCRA = LCDCRA|(1<<LCDEN);
	// Setting low power wave form
	write_8_field(&LCDCRA,1,1,LCDAB);
	//LCDCRA = LCDCRA|(1<<LCDAB);
	// disabling the interrupt
	write_8_field(&LCDCRA,0,1,LCDIF);
	//LCDCRA = LCDCRA&(~(1<<LCDIF));
	// Disabling blanking
	write_8_field(&LCDCRA,0,1,0);
	//LCDCRA = LCDCRA&(~(1));
	
	
	//-----------------------------------
	// Clock manipulation
	//-----------------------------------
	
	// setting the clock source to external
	write_8_field(&LCDCRB,1,1,LCDCS);
	//LCDCRB = LCDCRB|(1<<LCDCS);
	// Setting Bias
	write_8_field(&LCDCRB,1,0,LCD2B);
	//LCDCRB = LCDCRB&(~(1<<LCD2B));
	// Setting duty cycle
	write_8_field(&LCDCRB,3,2,LCDMUX0);
	//LCDCRB = LCDCRB|((0b11<<LCDMUX0));
	// Setting number of active segments to 25
	write_8_field(&LCDCRB,0b111,3,0);
	//LCDCRB = LCDCRB|(0b111);
	
	
	//-----------------------------------
	// Frame rate manipulation
	//-----------------------------------
	// Set n = 16
	write_8_field(&LCDFRR,0,3,LCDPS0);
	//LCDFRR = LCDFRR&(~(0b111<<LCDPS0));
	// Set D = 8
	write_8_field(&LCDFRR,0b111,3,0);
	//LCDFRR = LCDFRR|(0b111);
	
	
	//-----------------------------------
	// Contrast manipulation
	//-----------------------------------
	// Setting msb->msb-2 to 0 to set drive time to 300 us
	write_8_field(&LCDCCR,0,3,LCDDC0);
	//LCDCCR = LCDCCR&(~(7<< LCDDC0));
	// Setting lsb -> lsb+3 to 1 to set voltage to 3.35V
	write_8_field(&LCDCCR,15,4,0);
	//LCDCCR = LCDCCR|((15));
}

void write_char(char ch,int pos){
	if(pos < 0 || pos > 5)
	return;
	uint16_t num = 0x0;
	uint8_t *address = (uint8_t *)(0xEC+(pos>>1));
	
	if(ch>=48&& ch<=57){
		num = dict_arr[ch-48];
	}
	
	for( int i= 0; i < 4; i++){
		uint8_t nibble = num&0xf;
		num>>=4;
		
		if(pos%2==0)
		{
			*address = (*address)&0xf0;
			*address = (*address)|nibble;
		}
		else
		{
			*address = (*address)&0x0f;
			*address =  *address | nibble << 4;
		}
		address+=5;
		
	}
	
	
}

void print_at(int num, int first_pos, int length){
	if(first_pos+length> MAX_POS)
		return;
	for(int i = 0; i < length; i++){
		// Grab lowest digit
		int temp_num = num%10;
		// Remove lowest digit
		num = num/10;
		// if length+ first_pos exceeds the number of segments, wrap around
		write_char(temp_num+48,(first_pos+length-i)%MAX_POS);
	}
}
void write_string(char* ch, int first_pos){
	first_pos = first_pos%MAX_POS;
	for(int i = first_pos; i < MAX_POS; i++){
		if(*ch != '\0'){
			write_char(*ch,i);
			ch++;
		}
		else
		write_char(' ',i);
	}
}



void write_long(long num){
	int pos = 5;
	if(num == 0){
		write_char(48,5);
		for(int i = 0; i <=4; i++){
			write_char(0,i);
		}
		return;
	}
	while(num && pos >= 0){
		char buffer[2];
		int temp_num = num-(num/10)*10;
		num = num/10;
		int_to_str(temp_num,buffer);
		write_char(buffer,pos);
		pos--;
	}
	while(pos>=0){
		write_char(0,pos);
		pos--;
	}
}








/************************************************************************/
/*							HELPER SECTION                              */
/************************************************************************/

void swap_segment(void){
	
	LCDDR13 = LCDDR13^1;
	LCDDR18 = LCDDR18^1;
}

int is_prime(long num){
	
	if (num <= 3)
	return 1;
	
	if(num%2 == 0)
	return 0;
	
	long counter = 3;
	
	while(counter <num){
		if(num%counter == 0)
		return 0;
		counter++;
	}
	return 1;
}

void toggle_led(void){
	LCDDR8= LCDDR8^1;
}