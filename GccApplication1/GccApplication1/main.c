/*
 * GccApplication1.c
 *
 * Created: 2022-02-15 14:35:42
 * Author : ivarj
 */ 

#include <avr/io.h>


int main(void)
{
	volatile uint8_t * ptr = 0x012e;
	*ptr = 0;
    /* Replace with your application code */
    while (1) 
    {
		*ptr++;
		*ptr--;
		for(long i = 0; i < 1000000; i++);
		if(*ptr != 0){
		volatile int i = 0;
		}
    }
}

