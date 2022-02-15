#ifndef MYTEST_C
#define MYTEST_C
#include "../include/lcd_driver.h"
//#include "../include/tinythreads.h"
#include <stdbool.h>

mutex primes_mutex = MUTEX_INIT;
void computePrimes(int pos) {
    long n;
	
    for(n = 1; ; n++) {
        if (is_prime((long)n)) {
	        //printAt_task2(n,pos);
			//printAt_task1(n,pos);
            //printAt(n, pos);
			//yield();
        }
    }
}
void next_prime(long *num){
	while(1)
	{
		*num+=1;
		if(is_prime(*num)==1){
			return;
		}
	}
}
void primes(void){
	long num = 0;	
	
	lock(&primes_mutex);
	next_prime(&num);
	write_long(num);
	unlock(&primes_mutex);
	
}


int main() {
	LCDDR13 = LCDDR13|1;	
	lock(&primes_mutex);
	lock(&blink_mutex);
	lock(&button_mutex);
	init_lcd();
    spawn(blink,0);
	spawn(button,0);
    primes();
	return 0;
}
#endif
