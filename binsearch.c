#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void bubble_sort(unsigned int size, int * arr);
unsigned int binsearch(int * array, unsigned int size, int key);
unsigned int simplesearch(int * array, unsigned int size, int key);
void print(int *array, unsigned int count) {
	for (int i = 0; i < count; i++) {
		printf("%4d", array[i]);
	}
	printf("\n");
}

int main () {
	srand(time(NULL));
	int* array = NULL;
	unsigned int count = 0;
	scanf("%u", &count);
	array = (int*) malloc(sizeof(int) * count);
	for (int i = 0; i < count; i++) {
		array[i] = rand() % 10;
		// scanf("%d", array + i);
	}

	bubble_sort(count, array);

	int key = 0;
	scanf("%d", &key);

	// printf("found: %d", simplesearch(array, count, key));
	printf("found: %d", binsearch(array, count, key));
	printf("\n");
	return 0;
}

void bubble_sort(unsigned int size, int * arr) {
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < i; j++) {
            if (arr[i] < arr[j]) {
                arr[i] ^= arr[j];
                arr[j] ^= arr[i];
                arr[i] ^= arr[j];
            }
        }
    }
}

unsigned int simplesearch(int * array, unsigned int size, int key) {
	for (unsigned int i = 0; i < size; i++) {
		if (key == array[i]) {
			return i;
		}
	}
	return -1;
}

unsigned int binsearch(int * array, unsigned int size, int key) {
	// printf("size: %2d, central index: %2d, central el: %3d\n", size, size/2, array[size/2]);
	// print(array, size);
	if (size == 1 && array[0] != key) {
		return -1;
	}
	if (size == 1 && array[0] == key) {
		return 0;
	}
	if (array[size/2] == key) {
		return size/2;
	}
	if (array[size/2] < key) {
		int tmp = binsearch(array + size/2 + 1, size - size/2 - 1, key);
		return tmp == -1 ? tmp : size/2 + 1 + tmp;
	}
	if (array[size/2] > key) {
		return binsearch(array, size/2, key);
	}
	return -1;
}