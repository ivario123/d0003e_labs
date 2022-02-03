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
    write_char((num % 100) / 10 + '0', pp);
	for(volatile int i = 0; i <10000; i++);
	pp++;
    write_char( num % 10 + '0', pp);
	unlock(&pp_mutex);
}

void printAt_task2(long num, int pos) {
	int pp_1 = pos;
    write_char( (num % 100) / 10 + '0', pp_1);
	for(int i = 0; i <1000; i++);
	pp_1 = pos+1;
    write_char( num % 10 + '0', pp_1);
}

void printAt_task1(long num, int pos) {
	int pp_1 = pos;
	write_char( (num % 100) / 10 + '0', pp_1);
	yield();
	for(int i = 0; i <1000; i++);
	pp_1 = pos+1;
	write_char( num % 10 + '0', pp_1);
	yield();
}
void computePrimes(int pos) {
    long n;
	
    for(n = 1; ; n++) {
        if (is_prime((long)n)) {
	        //printAt_task2(n,pos);
			//printAt_task1(n,pos);
            printAt(n, pos);
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
	while(1){
		next_prime(&num);
		write_long(num);
	}
}


int main() {
	LCDDR13 = LCDDR13|1;	
	
	init_lcd();
    spawn(blink,0);
	spawn(button,0);
    primes();
	return 0;
}
#endif
