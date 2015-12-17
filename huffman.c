#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	unsigned char symbol;
	size_t freq;
	char bit_val[1024];
} freqs;

typedef struct {
	char symbol;
	char bit_val[1024];
} dict_element;

int comparator_by_freq(const void* p1, const void* p2) {
	return ((freqs*)p2)->freq - ((freqs*)p1)->freq;
}
int comparator_by_symbol(const void* p1, const void* p2) {
	return ((freqs*)p1)->symbol - ((freqs*)p2)->symbol;
}

freqs freq[256] = {0};

void build_dictionary(freqs* freq, size_t dict_size) {
	size_t bit_size = 0;
	size_t current_symbol = 0;
	char base[1024] = { 0 };
	//size_t current_symbol = 0;
	for (; current_symbol < dict_size && current_symbol < 253;) {
		strcpy(freq[current_symbol + 0].bit_val, base);
		strcpy(freq[current_symbol + 1].bit_val, base);
		strcpy(freq[current_symbol + 2].bit_val, base);
		strcat(freq[current_symbol + 0].bit_val, "00");
		strcat(freq[current_symbol + 1].bit_val, "01");
		strcat(freq[current_symbol + 2].bit_val, "10");
		current_symbol += 3;
		strcat(base, "11");
	}
}

void encrypt_file(char* input, char* output) {
	FILE *f = fopen(input, "r");
	fseek(f, 0, SEEK_END);
	unsigned long file_size = ftell(f);
	fseek(f, 0, SEEK_SET);

	unsigned char *file_data = (char*)malloc(file_size);
	fread(file_data, 1, file_size, f);
	fclose(f);

	for (size_t i = 0; i < file_size; i++) {
		freq[file_data[i]].freq++;
	}

	int flag = 1;
	for (size_t i = 0; i < 256; i++) {
		freq[i].symbol = i;
		if (freq[i].freq) {
			//printf("%c(%3d) - %d | ", (char)i, i, freq[i].freq);
			if (!flag++){
			//	printf("\n");
			}
			flag %= 5;
		}
	}
	//printf("\n");
	qsort(freq, 256, sizeof(freqs), comparator_by_freq);
	size_t dict_size = 0;
	for (size_t i = 0; i < 256; i++) {
		if (freq[i].freq) {
			dict_size++;
		}
	}

	build_dictionary(freq, dict_size);
	dict_element * dict = (dict_element*)malloc(sizeof(dict_element)*dict_size);
	for (size_t i = 0; i < dict_size; i++) {
		dict[i].symbol = freq[i].symbol;
		strcpy(dict[i].bit_val, freq[i].bit_val);
	}

	qsort(freq, 256, sizeof(freqs), comparator_by_symbol);

	size_t result_buf = 1000;
	char* result = (char*)malloc(result_buf);
	memset(result, 0, result_buf);
	for (size_t i = 0; i < file_size; i++) {
		strcat(result, freq[file_data[i]].bit_val);
		if (strlen(result) + 1024 > result_buf) {
			result_buf += 1000;
			result = (char*)realloc(result, result_buf);
		}
	}

	FILE * f_out = fopen(output, "w");
	fwrite(&dict_size, sizeof(dict_size), 1, f_out);
	fwrite(dict, sizeof(dict_element), dict_size, f_out);
	fwrite(result, 1, strlen(result), f_out);
	fclose(f_out);
	free(file_data);
	free(result);
	free(dict);
}



void decrypt_file(char* input, char* output) {
	FILE *f = fopen(input, "r");
	fseek(f, 0, SEEK_END);
	unsigned long file_size = ftell(f);
	fseek(f, 0, SEEK_SET);

	size_t dict_size = 0;
	fread(&dict_size, sizeof(size_t), 1, f);
	dict_element * dict = (dict_element*)malloc(sizeof(dict_element)*dict_size);
	fread(dict, sizeof(dict_element), dict_size, f);
	file_size -= ftell(f);
	unsigned char *file_data = (char*)malloc(file_size);
	fread(file_data, 1, file_size, f);
	fclose(f);

	size_t result_buf = 1000;
	char* result = (char*)malloc(result_buf);
	char tmp[2] = { 0 };
	memset(result, 0, result_buf);

	for (size_t i = 0; i < file_size;) {
		size_t symbol_size = 0;
		while (file_data[i + symbol_size] != '0' && file_data[i + 1 + symbol_size] != '0') {
			symbol_size += 2;
		}
		symbol_size += 2;
		char symbol[48] = { 0 };
		strncpy(symbol, file_data + i, symbol_size);

		i += symbol_size;
		for (size_t j = 0; j < dict_size; j++) {
			if (strcmp(dict[j].bit_val, symbol) == 0) {
				tmp[0] = dict[j].symbol;
				strcat(result, tmp);
				if (strlen(result) + 48 > result_buf) {
					result_buf += 1000;
					result = (char*)realloc(result, result_buf);
				}
				break;
			}
		}
	}

	FILE * f_out = fopen(output, "w");
	fwrite(result, 1, strlen(result), f_out);
	fclose(f_out);
	free(file_data);
	free(result);
	free(dict);
}


int main() {
	encrypt_file("input.jpg", "output.jpg");
	//decrypt_file("output.txt", "decrypted.txt");
	return 0;
}
