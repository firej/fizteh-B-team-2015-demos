#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct _bintreenode node;
typedef struct _bintreenode {
	int data;
	node* lchild;
	node* rchild;
} node;

typedef struct _bintree {
	node* root;
} bintree;

#define TREE_SIZE 10

void add_to_tree(bintree* tree, int data);
void print_tree(bintree* tree);
int get_depth(bintree* tree);
void del_tree(bintree* tree);
void del_node(bintree* tree, int data);
node* find_node(bintree* tree, int data);

int main() {
	bintree mytree = {0};
	srand(time(NULL));
    for (unsigned long long i = 0; i < TREE_SIZE; i++) {
        add_to_tree(&mytree, rand() % 100);
    }
    print_tree(&mytree);
    del_tree(&mytree);
	return 0;
}

void add_to_tree(bintree* tree, int data) {
	if (tree->root) {
		node* tmp = tree->root;
		for (;;) {
			if (data < tmp->data) {
				if (tmp->lchild) {
					tmp = tmp->lchild;
				}
				else {
					tmp->lchild = (node*)calloc(sizeof(node), 1);
					tmp->lchild->data = data;
					break;
				}
			}
			else {
				if (tmp->rchild) {
					tmp = tmp->rchild;
				}
				else {
					tmp->rchild = (node*)calloc(sizeof(node), 1);
					tmp->rchild->data = data;
					break;
				}
			}
		}
	}
	else {
		tree->root = (node*)calloc(sizeof(node), 1);
		tree->root->data = data;
	}
}

int max(int a, int b) {
	return a > b ? a : b;
}
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

int __get_depth(node* root) {
	if (root == NULL)
		return 0;
	return 1 + max(__get_depth(root->lchild), __get_depth(root->rchild));
	// return 1 + MAX(__get_depth(root->lchild), __get_depth(root->rchild));
	// return 1 + (((__get_depth(root->lchild)) > (__get_depth(root->rchild))) ? (__get_depth(root->lchild)): (__get_depth(root->rchild)))
}

int get_depth(bintree* tree) {
	return __get_depth(tree->root);
}

void print_slice(node ** array, unsigned int size, int height, int depth) {
	for (int i = 0; i < (height - depth) * 2 - 1; i++) {
		printf ("  ");
	}
	for (int i = 0; i < size; i++) {
		array[i] ? printf("%2d", array[i]->data) : printf("**");
		for (int j = 0; j < (height - depth) + 1; j++) {
			printf("  ");
		}
	}
	printf("\n");
}

void print_tree(bintree* tree) {
	unsigned int height = get_depth(tree);

	node* root = tree->root;
	node *arr[100], *arr2[100];
	unsigned int nodes;

	for (int i = 0; i < height * 2; i++) printf("  ");
	printf("%2d\n", root->data);

	arr2[0] = root;
	nodes = 1;

	int not_null_flag = 1;
	for(int depth = 2;not_null_flag; depth++) {
		not_null_flag = 0;
		for (int i = 0; i < nodes; i++) {
			arr[i*2] = arr2[i] ? arr2[i]->lchild : NULL;
			arr[i*2 + 1] = arr2[i] ? arr2[i]->rchild : NULL;
			if (arr[i*2] || arr[i*2 + 1]) not_null_flag = 1;
		}
		nodes *= 2;
		memcpy(arr2, arr, nodes * sizeof(node*));
		if (not_null_flag) {
			print_slice(arr2, nodes, height, depth);
		}
	}

}

void __del_tree_by_node (node* root) {
	if (root == NULL)
		return;
	__del_tree_by_node(root->lchild), __del_tree_by_node(root->rchild);
	free(root->lchild), free(root->rchild);
	root->lchild = NULL, root->rchild = NULL;
}

void del_tree(bintree* tree) {
	__del_tree_by_node(tree->root);
	free(tree->root);
	tree->root = NULL;
}

node* __find_node (node* root, int data) {
	if (!root || data == root->data)
		return root;
	return data < root->data ? __find_node(root->lchild, data) : __find_node(root->rchild, data);
}

node* find_node(bintree* tree, int data, node** parent) {
	return __find_node(tree->root, data, parent);
}


node* __find_node_p (node* root, int data, node** parent) {
	if (!root)
		return root;
	if (!root || data == root->data)
		return root;
	return data < root->data ? __find_node(root->lchild, data) : __find_node(root->rchild, data);
}


void __del_node(node* root, node* parent) {

}

void del_node(bintree* tree, int data) {
	node* node_for_del = find_node(tree->root, data);
	__del_node(node_for_del, )
}








