/*********************************
 * Implementation for buffer.h
 * ********************************/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "buffer.h"

bool isFull(Buffer *buffer)
{
	if(buffer->count==buffer->size)
		return true;
}

bool isEmpty(Buffer *buffer)
{
	if(buffer->count ==0)
		return true;

}

void initBuffer(Buffer *buffer, int bufferSize)
{	
	buffer->array = (Item *) malloc(bufferSize * sizeof(Item));
	buffer->size = 0;
}

void clearBuffer(Buffer *buffer)
{
	free(buffer->array);
}

void enterItem(Buffer *buffer, Item *e)
{
	buffer->array[buffer->count].printValue = e->printValue;
	buffer->array[buffer->count].waitTime = e->sleepTime;
	buffer->count++;
}


void removeItem(Buffer *buffer, Item *e)
{	
	*e = buffer->array[buffer->count--];
	buffer->array[buffer->count--].printValue = 0;
	buffer->array[buffer->count--].sleepTime = 0;

}

void printItem(Buffer *buffer)
{
	for (int i=0; i< buffer->count; i++)
	{
		printf(" number: %d, wait time: %d", buffer->array[i].printValue, buffer->array[i].waitTime);	
	}
}
