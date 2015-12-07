#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

typedef struct __item {
	double weight;
	double price;
	double cost;			// Удельная стоимость
	size_t num;
} item;

double size;
size_t items_count = 0;
item* items;
item* ideal_solution;
size_t solution_count = 0;
item* items_in_knap;
size_t knap_count = 0;

int comparator(const void* p1, const void* p2) {
	double res = ((const item*)p1)->cost - ((const item*)p2)->cost;
	if (res) {
		return res > 0 ? -1 : 1;
	}
	return 0;
}

void print(item* items, size_t size){
	for (size_t i = 0; i < size; i++){
		printf("%d\t%d\t%0.2lf\t%0.2lf\t%0.2lf\n", i, items[i].num, items[i].weight, items[i].price, items[i].cost);
	}
}


double get_knap_weight(item* items, size_t items_count) {
	double res = 0.0;
	for (size_t i = 0; i < items_count; i++) {
		res += items[i].weight;
	}
	return res;
}
double get_knap_price(item* items, size_t items_count) {
	double res = 0.0;
	for (size_t i = 0; i < items_count; i++) {
		res += items[i].price;
	}
	return res;
}

void add_to_knap(item **items_in_knap, size_t *knap_count, item current) {
	if (!*knap_count) {
		*items_in_knap = (item*)malloc(sizeof(item));
		*knap_count = 1;
	}
	else {
		*items_in_knap = (item*)realloc(*items_in_knap, sizeof(item)*(*knap_count + 1));
		*knap_count += 1;
	}
	(*items_in_knap)[*knap_count - 1] = current;
}

void try_to_solve(	item **items_in_knap, size_t *knap_count,
					item **ideal_solution, size_t *solution_count,
					item *items, size_t items_count) {
	if (*knap_count == 0) {
		for (size_t i = 0; i < items_count; i++) {
			if (get_knap_weight(*items_in_knap, *knap_count) + items[i].weight <= size) {
				add_to_knap(items_in_knap, knap_count, items[i]);
			}
		}
	}

	if (get_knap_price(*items_in_knap, *knap_count) > get_knap_price(*ideal_solution, *solution_count)) {
		free(*ideal_solution);
		*ideal_solution = (item*)malloc(sizeof(item)* *knap_count);
		memcpy(*ideal_solution, *items_in_knap, sizeof(item)* *knap_count);
		*solution_count = *knap_count;
	}

}





int main() {
	scanf("%lf", &size);
	scanf("%d", &items_count);
	items = (item*)malloc(sizeof(item)*items_count);
	for (size_t i = 0; i < items_count; i++) {
		scanf("%lf %lf", &items[i].weight, &items[i].price);
		if (items[i].weight == 0) {
			return -1;
		}
		items[i].cost = items[i].price / items[i].weight;
	}

	qsort(items, items_count, sizeof(item), comparator);

	for (size_t i = 0; i < items_count; i++) {
		items[i].num = i;
	}

	try_to_solve(&items_in_knap, &knap_count, &ideal_solution, &solution_count, items, items_count);
	print(ideal_solution, solution_count);

	printf("===================================\n");
	free(items_in_knap);
	knap_count = 0;
	try_to_solve(&items_in_knap, &knap_count, &ideal_solution, &solution_count, items+1, items_count-1);
	print(items_in_knap, knap_count);
	printf("===================================\n");
	print(ideal_solution, solution_count);



	return 0;
}