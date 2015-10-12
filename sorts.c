#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 10000000

void bubble_sort(unsigned int size, char * arr);
void qsort_sort(unsigned int size, char * arr);
void heap_sort(unsigned int size, char * arr);
int compar(const void * p1, const void * p2) {
    return 0; //*((char*)p1) - *((char*)p2);
}

void print (unsigned int size, char* arr) {
    for (int i = 0; i < ARR_SIZE; i++){
       printf("%5d", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
	int start_time = time(NULL);
    char *arr = (char*) malloc(ARR_SIZE * sizeof(char));
    for (unsigned long long i = 0; i < ARR_SIZE; i++) {
        arr[i] = rand() % 10000;
    }
    // bubble_sort(ARR_SIZE, arr);
    // qsort(arr, ARR_SIZE, sizeof(char), compar);
    // print(ARR_SIZE, arr);

    heap_sort(ARR_SIZE, arr);

	// printf("time: %d\n", time(NULL) - start_time);
    printf("\n");
    // print(ARR_SIZE, arr);
    free(arr);
    return 0;
}

void heapify(char * arr, unsigned int i, unsigned int j);
void heap_sort(unsigned int size, char * arr) {
	for (int i = size / 2 - 1; i >= 0; i--) {
		heapify(arr, (unsigned int)i, size);
	}

	for (unsigned int i = size - 1; i >= 1; i--) {
		arr[i] ^= arr[0];
		arr[0] ^= arr[i];
		arr[i] ^= arr[0];
		heapify(arr, 0, i);
    }
}

void heapify(char * arr, unsigned int i, unsigned int j) {
	char end = 0;
	unsigned int max;

	while ((i * 2 + 1 < j) && (!end)) {
        if (i * 2 + 2 == j)
            max = i * 2 + 1;
		else if (arr[i * 2 + 1] > arr[i * 2 + 2])
			max = i * 2 + 1;
		else
			max = i * 2 + 2;
		if (arr[i] < arr[max]) {
			arr[i] ^= arr[max];
			arr[max] ^= arr[i];
			arr[i] ^= arr[max];
			i = max;
		}
		else
			end = 1;
	}
}

void qsort_sort(unsigned int size, char * arr) {
    if (size == 1) {
        return;
    }
    unsigned int p = size/2;

    int i = 0, j = size - 1;
    for (;;) {
        for (; i <= j && i < size; i++) {
            if (arr[i] >= arr[p])
                break;
        }
        for (; j >= i && j >= 0; j--) {
            if (arr[j] <= arr[p])
                break;
        }
        if (i != j && arr[i] != arr[j]) {
            printf ("p: %d  i: %d j: %d, A[i]: %u  A[j]: %u\n", arr[p], i, j, arr[i], arr[j]);
            if (i == p)
                p = j;
            if (j == p)
                p = i;
            arr[i] ^= arr[j];
            arr[j] ^= arr[i];
            arr[i] ^= arr[j];
            // i++; j--;
        }
        else {
            break;
        }
    }
}

void bubble_sort(unsigned int size, char * arr) {
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
