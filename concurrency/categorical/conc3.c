#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>

#include "list.h"

#include "mt19937ar.c"

#define NUM_SEARCH 15
#define NUM_INS 5
#define NUM_DEL 3

void * searcher();
void * inserter();
void * deleter();
//void * threadWorker();

node_t *list = NULL;  
sem_t notSearching, notInserting; //Make sure deleter is running by itself
sem_t insertSem, searchMutex;  // Cliquez for dayz
sem_t insertMutex; //For inserter to run in parallel

int numSearcher =0, numInserter =0;	//for keeping deleter out


void * searcher()
{

	sem_wait(&searchMutex);				
	numSearcher++;
	//lock right to search
	if(numSearcher ==1)
	{
		sem_wait(&notSearching);		
	}

	sem_post(&searchMutex);				
  
    //unsigned long seed = time(NULL);
    //init_genrand(seed);
	//int val = genrand_int31()%100;
	int val = rand()%100;
	//printf("\tSearching: %d\t 1 if found: %d\n", val, searchList(list, val));
	printf("\tSearching: %d\n", val);
	searchList(list, val);
	printf("\tDone searching\n");

	sem_wait(&searchMutex);				
	numSearcher--;
	//no more searches
	if(numSearcher ==0)					
	{
		sem_post(&notSearching);		
	}

	sem_post(&searchMutex);
	sleep(3);
	return NULL;
}

void * inserter()
{

	sem_wait(&insertMutex);				
	numInserter++;
	//lock right to insert
	if(numInserter ==1)
	{
		sem_wait(&notInserting);		
	}
	sem_post(&insertMutex);			
	sem_wait(&insertSem);
   
    //unsigned long seed = time(NULL);
    //init_genrand(seed);
	//int val = genrand_int31()%100;
    
    int val = rand()%100;
	printf("\nInserting: %d\n", val);
	list = insertNode(list, val);
	//printList(list);
	printf("Done Inserting\n");

	sem_post(&insertSem);
	sem_wait(&insertMutex);

	numInserter--;

	if(numInserter ==0)
	{
		sem_post(&notInserting);
	}

	sem_post(&insertMutex);
	sleep(3);
	return NULL;
}

void * deleter()
{
	//make sure mutually exclusive with searches and insertions
	sem_wait(&notSearching);
	sem_wait(&notInserting);
	//unsigned long seed = time(NULL);
	//init_genrand(seed);
	//int val = genrand_int31()%100;
	int val = rand()%100;
	printf("Removing: %d\n", val);
	list = removeNode(list, val);
	//printList(list);
	printf("Done Removing\n");

	sem_post(&notInserting);
	sem_post(&notSearching);
	sleep(3);
	return NULL;
}
/*
void * threadWorker()
{
	while(1)
	{
		inserter();
		searcher();
		deleter();

	}

}
*/


int main(int argc, char* argv[])
{
	int i=0;
	
	pthread_t searchers[NUM_SEARCH];
	pthread_t inserters[NUM_INS];
	pthread_t deleters[NUM_DEL];
	
	//pthread_t threadz[10];
 	

	sem_init(&notSearching,0,1);
	sem_init(&notInserting,0,1);
	sem_init(&insertSem,0,1);
	sem_init(&searchMutex,0,1);
	sem_init(&insertMutex,0,1);


	for(i=0; i< NUM_INS; i++)
	{
		pthread_create(&inserters[i], NULL, inserter, NULL);
	}

	for(i=0; i< NUM_SEARCH; i++)
	{
		pthread_create(&searchers[i], NULL, searcher, NULL);
	}

	for(i=0; i< NUM_DEL; i++)
	{
		pthread_create(&deleters[i], NULL, deleter, NULL);
	}

	

	for (i = 0; i < NUM_INS; i++) {
		pthread_join(inserters[i], NULL);
	}

	for (i = 0; i < NUM_SEARCH; i++) {
		pthread_join(searchers[i], NULL);
	}

	for (i = 0; i < NUM_DEL; i++) {
		pthread_join(deleters[i], NULL);
	}
/*
	for(i=0; i< 5; i++)
	{
		pthread_create(&threadz[i], NULL, threadWorker, NULL);
	}

	for (i = 0; i < 5; i++) {
		pthread_join(threadz[i], NULL);
	}
*/
	sem_destroy(&notSearching);
	sem_destroy(&notInserting);
	sem_destroy(&insertSem);
	sem_destroy(&searchMutex);
	sem_destroy(&insertMutex);
	freeList(&list);



return 0;
}




