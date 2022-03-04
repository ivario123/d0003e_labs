#include "../include/lcd_driver.h"

/************************************************************************/
/*								TASK 1									*/
/************************************************************************/
void init_lcd(void){
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


/************************************************************************/
/*							HELPER SECTION                              */
/************************************************************************/

void print_at(uint8_t num, uint8_t pos, uint8_t width){
	for(int i = width-1; i >= 0; i--){
		uint8_t temp = num%10;
		num = num/10;
		write_char(temp+48,pos+i);
	}
}