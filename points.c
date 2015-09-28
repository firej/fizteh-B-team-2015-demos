/*
Напишите код для нахождения k ближайших точек к заданной точке.
Программа сначала получает на вход набор точек на плоскости:
количество точек n, затем идет последовательность из n строк,
каждая из которых содержит два числа: координаты точки.
Величина n не превосходит 1000, все исходные координаты –
целые числа, не превосходящие 1000. Затем идет число запросов
m и m строк с двумя целыми числами, разделенными пробелом:
индекс i точки и сколько ближайших соседей надо вывести.
Индексы нумеруются с 0. Число запросов m >> n.
(препроцессинг, сортировка пузырьком и запоминание порядка для
каждой вершины).
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct {
	int x, y;
} point;

void get_nearest_points(point*, unsigned int, unsigned int, unsigned int);

int main (){
	unsigned int n = 0;
	scanf("%u", &n);

	printf("\x1b[0;31m");
	point *array = (point*)malloc(sizeof(point) * n);
	for (size_t i = 0; i < n; i++) {
		scanf("%d %d", &array[i].x, &array[i].y);
	}

	unsigned int m = 0;
	scanf("%u", &m);

	for (size_t i = 0; i < m; i++) {
		unsigned int index, count;
		scanf("%u %u", &index, &count);

		get_nearest_points(array, n, index, count);
		// printf("point with index: %d has coordinates (%d,%d)\n",
		//     index, array[index].x, array[index].y);
	}
	free(array);
	return 0;
}

float get_distance(point a, point b) {
	return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

void bubble_sort(unsigned int size, point* arr, point p) {
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < i; j++) {
            if (get_distance(p, arr[i]) < get_distance(p, arr[j])) {
                point tmp = arr[j];
                arr[j] = arr[i];
                arr[i] = tmp;
            }
        }
    }
}

void get_nearest_points(point* array,
						unsigned int size,
						unsigned int index,
						unsigned int count) {
	point *array_copy = (point*)malloc(sizeof(point) * size);
	memcpy(array_copy, array, sizeof(point)*size);
	bubble_sort(size, array_copy, array_copy[index]);
	printf("Точки, ближайшие к (%d,%d):", array[index].x, array[index].y);
	for (size_t i = 1; i <= count; i++) {
		printf(" (%d,%d){%3.1f}", array_copy[i].x, array_copy[i].y,
			get_distance(array_copy[i], array[index]));
	}
	printf("\n");
	free(array_copy);
}












