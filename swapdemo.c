#include <stdlib.h>
#include <stdio.h>

void swap(void* var1, void* var2, size_t size){
	for (int i = 0; i < size; i++) {
		*((char*)var1 + i) ^= *((char*)var2 + i);
		*((char*)var2 + i) ^= *((char*)var1 + i);
		*((char*)var1 + i) ^= *((char*)var2 + i);
	}
}

int main(){
	double a = 0., b = 1.;
	swap(&a, &b, sizeof(double));
	printf("a=%lf, b=%lf\n", a, b);
	return 0;
}
