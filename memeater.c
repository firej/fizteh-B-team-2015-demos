#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main () {
	for (;;) {
		int * ptr = (int*)malloc(4000000);
		if (ptr == NULL) {
			printf("Got NULL");
		}
		else {
			memset(ptr, 0, 4000000);
		}
	}


	return 0;
}