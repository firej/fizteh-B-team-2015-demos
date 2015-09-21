#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node_t node;
struct node_t {
	unsigned int somedata;
	struct {
		char *fio;
		unsigned long long age;
		char sex;
		unsigned long height;
		char *address;
	} user;
	node* prev;
	node* next;
};

typedef unsigned char bool;
#define true (1)
#define false (0)

bool create_list(node** list);
bool add_node(node** list, unsigned int data);
int get_data(node* list, size_t index);
bool set_data(node* list, size_t index, int data);
void print_list(node *list);
bool del_node(node** list, size_t index);

int main() {
	srand(time(NULL));
	node* list = NULL;
	for (int i = 0; i < 10; i++) {
		add_node(&list, rand() % 100);
	}

	print_list(list);

	set_data(list, 1, 50);
	del_node(&list, 0);

	print_list(list);

	// printf("%lu, %lu, %lu\n", sizeof(list->user), sizeof(list->next), sizeof(*list));

	// printf("%d\n", list->somedata);
	// printf("%d\n", list->next->somedata);
	// printf("%d\n", list->next->next->somedata);

	// printf("%d\n", get_data(list, 4));
	//printf("%d\n", list->next->next->next->somedata);
	return 0;
}

bool create_list(node** list) {
	*list = (node *)malloc(sizeof(node));
	return true;
}

bool add_node(node** list, unsigned int data) {
	if (*list == NULL) {
		create_list(list);
		(*list)->somedata = data;
		(*list)->next = NULL;
	}
	else {
		node* n = *list;
		for (; n->next != NULL ;)
			n = n->next;
		n->next = (node*) malloc(sizeof(node));
		n->next->somedata = data;
		n->next->next = NULL;
	}
	return true;
}

int get_data(node *list, size_t index) {
	node *n = list;
	int i = 0;
	for (; n->next != NULL && i < index; i++) {
		// printf("%d %d 0x%X\n", i, n->somedata, n->next);
		n = n->next;
	}
	if (i == index) {
		return n->somedata;
	}
	else {
		return 0;
	}
}

bool set_data(node *list, size_t index, int data) {
	node *n = list;
	int i = 0;
	for (; n->next != NULL && i < index; i++) {
		n = n->next;
	}
	if (i == index) {
		n->somedata = data;
		return true;
	}
	else {
		return false;
	}
}

void print_list (node* list) {
	node *n = list;
	while (n != NULL) {
		printf("%d\t", n->somedata);
		n = n->next;
	};
	printf("\n");
}

bool del_node(node** list, size_t index) {
	node *n = *list;
	node *prev = *list;
	if (index == 0) {
		*list = (*list)->next;
		free(n);
		return true;
	}

	int i = 0;
	for (; n->next != NULL && i < index; i++) {
		prev = n;
		n = n->next;
	}
	if (i == index) {
		prev->next = n->next;
		free(n);
		return true;
	}
	else {
		return false;
	}
}


















