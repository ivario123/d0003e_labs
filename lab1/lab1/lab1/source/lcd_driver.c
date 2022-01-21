/*
 * lcd_driver.c
 *
 * Created: 2022-01-21 08:21:07
 *  Author: ivarj
 */ 



int write_char(char ch,int pos){
	if(pos >MAX_POS||pos<MIN_POS)
	return -1;
	// The address of the first segment of the display
	uint8_t *first_addr = LCDDR0;
	// The numbers 0-9, credit wikipedia might be wrong
	
	return success;
}

int init_lcd(){
		
		
		// enabling the lcd
		*LCDCRA = (*LCDCRA)|(1<<LCDEN);
		// Setting low power wave form
		*LCDCRA = (*LCDCRA)|(1<<LCDAB);
		// disabling the interrupt
		*LCDCRA = (*LCDCRA)&(~(1<<LCDIF));
		// Disabling blanking
		*LCDCRA = (*LCDCRA)&(~(1));
		
		
		// setting the clock source to external
		*LCDCRB = (*LCDCRB)&(~(1<<LCDCS));
		*LCDCRB = (*LCDCRB)&(~(1<<LCD2B));
		*LCDCRB = (*LCDCRB)&(~(3<<LCDMUX0));
		
		
		
		
		// Setting the contrast voltage to3.35v and drive time to 300ms
		*LCDCCR = (*LCDCCR)&0b11111000;
		// Setting the
		*LCDFRR = (*LCDFRR)&0b10001111;
		return success;
}