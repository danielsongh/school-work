/*******
 * Header file for buffer implementation
 ******/

#ifndef BUFFER_H
#define BUFFER_H

#include <stdio.h>
#include <stdbool.h>
typedef struct
{
	int printValue;
	int sleepTime;

}Item;

typedef struct
{
	Item *array;
	int size;
	int count;	

}Buffer;

void initBuffer(Buffer *buffer, int bufferSize);
void clearBuffer(Buffer *buffer);
void enterItem(Buffer *buffer, Item *e);
void removeItem(Buffer *buffer, Item *e);
void printItem(Buffer *buffer);
bool isEmpty(Buffer *buffer);
bool isFull(Buffer *buffer);

#endif
