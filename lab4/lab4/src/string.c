
void revese(char* str){
	// O(n) Memory algorithm for reversing string
	// First find the end of the string
	char * eos = str;
	while(*eos!='\0')
		eos++;
	eos--;
	// Then loop until the end pointer has passed the start pointer
	while(eos>=str){
		// Temp variable used for swapping
		char temp = *eos;
		// swap the chars
		*eos = *str;
		*str = temp;
		// Decrement/increment
		eos--;
		str++;
	}
}

void n_least_signigicant(long num, int *ret, int n){
	*ret = num;
	for(int i = 0; i < n; i++)
		*ret = *ret-(*ret/10)*10;
	
}
void six_least_significant(long num,int *ret){
	// Plucks out the six least significant 
	*ret = (int)(num-(num/1000000)*1000000);
}
void int_to_str(int num,char* buffer){
	// Base case
	if (num == 0){
		*buffer = 48;
		*(++buffer) = '\0';
		return;
	}
	// Track start of string
	char * start = buffer;
	// Loop until num == 0
	while (num)
	{
		// Pluck out the least significant digit and convert it to a char
		*buffer = (volatile char) num-(num/10)*10+48;
		// remove the least significant digit
		num/=10;
		buffer++;
	}
	// Terminate string
	*buffer = '\0';
	// Reverse the string to make it readable
	revese(start);
}