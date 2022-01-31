#ifndef MYTEST_C
#define MYTEST_C
#include "../include/tinythreads.h"
#include "../include/lcd_driver.h"
#include <stdbool.h>

int pp = 0;
mutex pp_mutex = MUTEX_INIT; 
//void writeChar(char ch, int pos); // from lab 1

//bool is_prime(long i); // from lab 1

void printAt(long num, int pos) {
	lock(&pp_mutex);
	pp = pos;
    write_char( (num % 100) / 10 + '0', pp);
	unlock(&pp_mutex);
	for(int i = 0; i <1000; i++);
	pp = pos+1;
	lock(&pp_mutex);
    write_char( num % 10 + '0', pp);
	unlock(&pp_mutex);
}

void computePrimes(int pos) {
    long n;
	
    for(n = 1; ; n++) {
        if (is_prime((long)n)) {
            printAt(n, pos);
			//yield();
        }
    }
}


int main() {
	init();
	init_lcd();
    spawn(computePrimes, 0);
    computePrimes(3);
	return 0;
}
#endif
