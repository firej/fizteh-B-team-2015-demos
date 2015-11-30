#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

typedef unsigned char byte;

char* get_lcs(char*str1, char *str2);

int main(){ 
	char string1[1024] = {0}, string2[1024] = {0};
	gets(string1);
	gets(string2);

	get_lcs(string1, string2);

	return 0; 
}

#define MAX(x,y) ((x>y)?(x):(y))

void strrev(char* string) {
	unsigned int len = strlen(string);
	for (unsigned int i = 0; i < len/2; i++) {
		string[i] ^= string[len - i - 1];
		string[len - i - 1] ^= string[i];
		string[i] ^= string[len - i - 1];
	}
}

char* get_lcs(char *str1, char *str2) {
	unsigned int len1 = strlen(str1) + 1;
	unsigned int len2 = strlen(str2) + 1;
	byte * matrix = (byte*)calloc(len1*len2, sizeof(byte));

	for (unsigned int i = 0; i < len1; i++) {
		for (unsigned int j = 0; j < len2; j++) {
			if (i == 0 || j == 0)
				matrix[i*len2 + j] = 0;
			else if (str1[i-1] == str2[j-1])
				matrix[i*len2 + j] = matrix[(i-1)*len2 + j-1] + 1;
			else
				matrix[i*len2 + j] = MAX(matrix[(i-1)*len2 + j], matrix[i*len2 + j-1]);
		}
	}

	unsigned int j = len2 - 1;
	char res[1024] = {0};
	unsigned int res_ind = 0;
	for (unsigned int i = len1 - 1; i > 0; i--){
		if (matrix[(i-1)*len2 + j] != matrix[(i)*len2 + j]) {
			res[res_ind++] = str1[i-1];
			j--;
		}
	}

	strrev(res);
	for (unsigned int i = 0; i < len1; i++) {
		for (unsigned int k = 0; k < len2 && i == 0; k++) {
			printf("%2d ", k);
		}
		if (i == 0) printf("\n");
		for (unsigned int j = 0; j < len2; j++) {
			printf("%2d ",matrix[i*len2 + j]);
		}
		printf("\n");
	}


	printf("%s\n%s\n%d\n", str1, str2, matrix[(len1 - 1) * len2 + len2 - 1]);
	printf("%s\n\n", res);
	return str1;
}