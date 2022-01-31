#ifndef MYTEST_C
#define MYTEST_C
#include "../include/tinythreads.h"
#include "../include/lcd_driver.h"
#include <stdbool.h>

//void writeChar(char ch, int pos); // from lab 1

//bool is_prime(long i); // from lab 1

void printAt(long num, int pos) {
    int pp = pos;
    write_char( (num % 100) / 10 + '0', pp);
    pp++;
    write_char( num % 10 + '0', pp);
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
