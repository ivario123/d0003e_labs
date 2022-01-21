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
	uint8_t char_arr[] = {0xC3F,0x406,0xDB,0x8F,0xE6,0xED,0xFD,0x1401,0xFF,0xE7};
	
	return success;
}

int init_lcd(){
		
		
		
		
		// Setting the contrast voltage to3.35v and drive time to 300ms
		LCDCCR = LCDCCR&0b11111000;
		// Setting the
		LCDFRR = LCDFRR&0b10001111;
		return success;
}