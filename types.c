#include <stdlib.h> 
#include <stdio.h>

int main(){ 
	printf("%lu %lu %lu %lu %lu %lu %lu", sizeof(char), sizeof(short), 
	sizeof(int), sizeof(long int), sizeof(long long), 
	sizeof(long double), sizeof(__int64_t)); 
	getchar(); 
	return 0; 
}