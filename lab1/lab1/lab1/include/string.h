/*
 * string.h
 *
 * Created: 2022-01-24 13:56:19
 *  Author: ivarj
 */ 


#ifndef STRING_H_
#define STRING_H_



/**
* Reverses a given string.
* @param str the string that should be reversed
* @return 0 if success
**/
int revese(char* str);
/**
* Plucks out the six least significant digits in base 
* @param num the number which to truncate
* @param ret the return value address
**/
void six_least_significant(long num,int * ret);
/**
* Converts an int to a string
* @param num the number which should be converted
* @param buffer the char pointer buffer to be overwritten
**/
int int_to_str(int num,char* buffer);


#endif /* STRING_H_ */