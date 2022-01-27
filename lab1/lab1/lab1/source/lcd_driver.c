#define CLOCK_SPEED 8000000  				// The clock speed in Hz
#define REFRESH_RATE 31250					// A second measured in bits of the timer register

// Our dicitonary
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


void write_char(char ch,int pos){
	// Writes a char to the lcd on possition pos
	if(pos < 0 || pos > 5)
		return;
	// Predefine num
	uint16_t num = 0x0;
	// Set the first address to LCDDR0
	uint8_t *first_address = (uint8_t *)0xEC;
	// set the address we are using to the first address offset by the floored division of pos/2
	// This is done since a 8 bit register is shared among neighboring positions, so the lower bits
	// correspond to the even numbered positions and the higher bits correspond to the odd numbered positions
	uint8_t *address = first_address+(pos>>1);
	
	// Set num to a value if exists in array
	if(ch>=48&& ch<=57){
		num = dict_arr[ch-48];
	}
	// Else it will clear the segment by writing 0 to it
	
	// Loop over every nibble i.e. 4 itterations
	for( int i= 0; i < 4; i++){
		// Always grab the lowest 4 bits of the char as nibble
		uint8_t nibble = num&0xf;
		// Remove lsb-lsb+4
		num>>=4;
		
		// Check if pos is even or odd
		if(pos%2==0)
		{	
			// Clear the bits we want to write over
			*address = (*address)&0xf0;
			// Write the data to the lower 
			*address = (*address)|nibble;
		}
		else
		{
			*address = (*address)&0x0f;
			*address =  *address | nibble << 4;
			// Write the data to the higher bits
		}
		// increment the address by 5*8bits
		address+=5;
		
	}
	
	
}
void write_string(char* ch, int first_pos){
	// Writes a string to the lcd, wraps around for lengths of string > 6
	first_pos = first_pos%MAX_POS;
	// loop until end of string
	while(*ch != '\0'){
		// Write the char to the lcd
		write_char(*ch,first_pos);
		// Increment the position
		first_pos++;
		// wrap around if needed
		first_pos = first_pos%MAX_POS;
		ch++;
	}
}
/************************************************************************/
/*				This function could be shortened significantly,	        */
/*			I do however feel that this is its most readable form		*/
/************************************************************************/
void init_lcd(void){
	
	
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
}


void write_long(long num){
	// Writes a long int to the display
	int temp; // Temporary int buffer
	six_least_significant(num,&temp);
	// Declare a 7 character buffer to store the char representation of the number
	char buffer[7];
	// Convert the int to a string
	int_to_str(temp,buffer);
	// Write the string to the display
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
	// Check all numbers n = 3 ... num since optimizing is not allowed
	while(counter <num){
		if(num%counter == 0)
		return 0;
		// In reality you would increment by two.
		counter++;
	}
	return 1;
}

void primes(void){
	// Simply generates primes
	long num = 0; // Set start value
	while(1)
	{
		// Only check odd numbers, helps a bit for larger numbers
		// This also catches num%2 == 0 inputs
		if(num >= 3){
			if (num % 2 == 0)
				num++;
			else
				num +=2;
		}
		else
			num++;
		if(is_prime(num)==1){
			// Write the num to display if it is a prime
			write_long(num);
		}
	}
}

void toggle_led(void){
	// If the segment is on turn it of
	if((LCDDR0&2)>>1== 0)
	LCDDR0 = LCDDR0|2;
	// Else turn it on
	else
	LCDDR0= LCDDR0^2;
}
void blink(void){
	uint16_t freq = 31250/2;		// The segment should turn on and of every half cycle i.e. flicker with 2 Hz frequency
	uint16_t last_time = TCNT1;
	// uint16t's wrap around in the same way for timer and normal addition
	while(1){
		while(((uint16_t)TCNT1)!= last_time+freq);
		last_time =(uint16_t)TCNT1;
		toggle_led();
	}
}

















void toggle_led_2(void){
	// Could remove the if statement but this is more readable
	if((LCDDR8&1)== 0)
	LCDDR8 = LCDDR8|1;
	else
	LCDDR8= LCDDR8^1;
}


void blink_2(void){
	// Could remove the if statement but this is more readable
	
	if((LCDDR8&1)== 0)
	LCDDR8 = LCDDR8|2;
	else
	LCDDR8= LCDDR8^2;
}