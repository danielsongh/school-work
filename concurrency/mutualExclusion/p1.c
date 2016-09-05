#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>


#define NUM_THREADS 5

sem_t mutex;
pthread_cond_t cond;
pthread_mutex_t lock;
int active =0;
bool mustWait= true;


//int thread_ID[NUM_THREADS] = { 1, 2, 3, 4, 5};

void * threadWorker(void *id);



int main(int argc, char* argv[]){

long i;
int rc;
pthread_t threads[NUM_THREADS];


sem_init(&mutex, 0, 3);
pthread_cond_init(&cond, NULL);
pthread_mutex_init(&lock, NULL);



printf("number of MAX threads: %d\n", NUM_THREADS);


for (i=0; i < NUM_THREADS; i++)
{
	
	rc = pthread_create(&threads[i], NULL, threadWorker, (void *)i);
	if (rc)
	{
		printf("pthread create error");
		exit(-1);
	}
}

for( i =0; i< NUM_THREADS; i++)
{
	pthread_join(threads[i], NULL);
}

sem_destroy(&mutex);

pthread_cond_destroy(&cond);
pthread_exit(NULL);
	
}


void * threadWorker(void *threadid){

	long tid;
	tid = (long)threadid;


	sem_wait(&mutex);
	

	pthread_mutex_lock(&lock);

	++active;
	
	if(active == 3)
	{
		mustWait = true;
	}

	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&lock);

	//crit sec
	printf("\t\t\t\t\tThread # %ld using resource\n", tid+1);
	sleep(2);
	printf("\t\t\t\t\t%d threads active\n", active);


	pthread_mutex_lock(&lock);
	
	--active;
	
	if(active ==0)
	{
		mustWait = false;
	}
	
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&lock);


	sem_post(&mutex);
	printf("thread # %ld exiting\n", tid+1);


	pthread_exit(NULL);
}

