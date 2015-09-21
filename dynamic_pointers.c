#include <stdio.h>
#include <stdlib.h>

int var = 0;


int foo(int array_size) {
	int b = 1, c;
	int stackarr[100] = {0};
	int *array = (int *)malloc(array_size * sizeof(b));
	var++;
	// printf("%d\n", var);
	// printf("%lu\n", sizeof(stackarr));
	printf("%lu\n", sizeof(array[0]));
	float f = 0;
	if ((float)b < f) {
		printf("Этот текст никогда не выведется");
	}
    return 0;
}

void bar(size_t size) {
	int *array = (int *)malloc(size * sizeof(int));

	for (int i = 0; i < size; i++) {
		// array[i] = i;
		*(array + i) = i;
	}

	for (int i = 0; i < size; i++) {
		// printf("%d\t", array[i]);
		printf("%d\t", *(array + i));
		printf("0x%X\t", (array + i));
	}
	printf("\n");

}

int main() {
	// foo(10);
	bar(10);
	return 0;
}