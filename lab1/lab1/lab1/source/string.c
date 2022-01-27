
void revese(char* str){
	char * eos = str;
	while(*eos!='\0')
	eos++;
	eos--;
	while(eos>=str){
		char temp = *eos;
		*eos = *str;
		*str = temp;
		eos--;
		str++;
	}
	return 0;
}
void six_least_significant(long num,int *ret){
	*ret = (int)(num-(num/1000000)*1000000);
}
void int_to_str(int num,char* buffer){
	if (num == 0){
		*buffer = 48;
		*(++buffer) = '\0';
		return 0;
	}
	char * start = buffer;
	while (num)
	{
		*buffer = (volatile char) num-(num/10)*10+48;
		num/=10;
		buffer++;
	}
	*buffer = '\0';
	revese(start);
	return 0;
}