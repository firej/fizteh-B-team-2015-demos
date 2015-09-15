#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARR_SIZE 10
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
int main(int argc, char *argv[]) {
    srand(time(NULL));
    char arr[ARR_SIZE] = { 0 };
    for (int i = 0; i < ARR_SIZE; i++) {
        arr[i] = rand() % 100;
    }
    bubble_sort(ARR_SIZE, arr);
    for (int i = 0; i < ARR_SIZE; i++){
        printf("%5d", arr[i]);
    }
    printf("\n");
    return 0;
}
 