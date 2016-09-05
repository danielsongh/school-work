/********************
 * HW 1 Producer-Consumer
 * 10/12/15
 ***********************/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "buffer.h"

void* produce(void *buffer);
void* consume(void *buffer);

pthread_mutex_t theMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t bufferNotFull = PTHREAD_COND_INITIALIZER;
pthread_cond_t bufferNotEmpty = PTHREAD_COND_INITIALIZER;

int main (int argc, char* argv[])
{	
	

	//inittialize buffer
	Buffer buffer;
	initBuffer(&buffer, 32);
	//producer and consumer threads
	pthread_t producer, consumer;

	//create new threads for produce and consume function
	pthread_create(&producer, NULL, produce, &buffer);
	pthread_create(&consumer, NULL, consume, &buffer);

	pthread_join(producer, NULL);
	pthread_join(consumer, NULL);

	printItem(&buffer);
	clearBuffer(&buffer);

	return 0;
}

void *produce(void *buffer)
{
	Item e;
	Buffer *b = (Buffer *)buffer;
	unsigned waitTime;
	__builtin_ia32_rdrand32_step(&waitTime);
	std::mt19937 gen(waitTime);
	waitTime= ^= gen();

	
	for (;;)
	{
		//mutex lock to protect the buffer
		pthread_mutex_lock(&theMutex);
		if(isFull(buffer) == 1)
		{	
			pthread_cond_wait(&bufferNotFull, &theMutex);
		}
		//enter item....
		enterItem(buffer, &e);
		//unlock	
		pthread_mutex_unlock(&theMutex);
	}
}

void *consume(void *buffer)
{
	Item e;
	
	for(;;)
	{
		//lock to protect the buffer
		pthread_mutex_lock(&theMutex);

		if(isEmpty(buffer) == 1)
		{
			pthread_cond_wait(&bufferNotEmpty, &theMutex);
		}
		//print then remove consumed item
		printItem(buffer);
		removeItem(buffer, &e);
		//unlock
		pthread_mutex_unlock(&theMutex);
	}

}
