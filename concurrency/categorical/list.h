#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node * next;
} node_t;

node_t * createNode(int val);
node_t * insertNode(node_t * head, int val);
node_t * removeNode(node_t * curr, int val);
int searchList(node_t * head, int val);

void printList(node_t * head);
void freeList(node_t ** head);

#endif
