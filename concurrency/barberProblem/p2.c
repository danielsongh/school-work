#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_CUSTOMERS 20


int allDone;
int sleeping;


long num_customers, num_chairs;

sem_t waiting_room;	//limit number of customers allowed to enter
sem_t mutex_chair;	//mutex barber chair
sem_t barber_ready;	//allow the barber to sleep until there is a customer
sem_t customer_ready;	//make sure customers wait until they get their haircut

void* barber(void*);
void* customer(void* num);
void cut_hair();
void get_hair_cut(int);
int empty_waiting_room();

void* barber(void* none) {
	printf("Barber: open\n");
	while (!allDone) 
	{
		if (empty_waiting_room()) 
		{
			sleeping = 1;
			sleep(3);
		}
		
		sem_wait(&barber_ready);
		if (!allDone) 
		{			 
			cut_hair();			 
			sem_post(&customer_ready);
		}
	}

	printf("The barber goes home\n");

	pthread_exit(NULL);
}

void cut_hair() {
	printf("\t\tBarber is cutting hair\n");
}

void* customer(void* number) {
	int num = *(int *)number;


	printf("Customer %d arrives at the shop\n", num);
	
	sem_wait(&mutex_chair);
	//if no chair available 
	if (sem_trywait(&waiting_room)) 
	{
		printf("Waiting room full: Customer %d leaves the shop\n", num);		
		sem_post(&mutex_chair);
	}
	else 
	{
		sem_post(&mutex_chair);

		printf("Customer %d enters the waiting room.\n", num);			
		sem_wait(&mutex_chair);
		sem_post(&waiting_room);
		if (sleeping)
		{
			printf("Customer %d wakes up the barber.\n", num);
		}
		sem_post(&barber_ready);
		
		sem_wait(&customer_ready);
		get_hair_cut(num);
		
		sem_post(&mutex_chair);
	}

	
	pthread_exit(NULL);
}



void get_hair_cut(int num) {
	
	printf("\t\tCustomer %d gets hair cut.\n", num);
}

//checks if there are available chairs
int empty_waiting_room() {
	int val;
	sem_getvalue(&waiting_room, &val);
	return (val == num_chairs);
}


int main(int argc, char* argv[]) {
	int i;
	
	long id[MAX_CUSTOMERS];
	allDone = 0;
	sleeping = 0;
	
	pthread_t barber_tid;
	pthread_t customer_tid[MAX_CUSTOMERS];

	if (argc != 3)
	{
		printf("./a.out <num_chairs> <num_customers>\n");
		exit(-1);
	}

	num_chairs = atoi(argv[1]);
	num_customers = atoi(argv[2]);

	if (num_customers > MAX_CUSTOMERS)
	{
		printf("Max customer: %d.\n", MAX_CUSTOMERS);
		exit(-1);
	}



	sem_init(&waiting_room, 1, num_chairs);
	sem_init(&mutex_chair, 1, 1);
	sem_init(&barber_ready, 1, 0);
	sem_init(&customer_ready, 1, 0);

	//BARBER
	pthread_create(&barber_tid, NULL, barber, NULL);
	
	//CUSTOMERS
	for (i=0; i<num_customers; i++)
	{
		id[i] = i;
		pthread_create(&customer_tid[i], NULL, customer, (void*)&id[i]);
	}
	
	//join
	for (i=0; i<num_customers; i++)
		pthread_join(customer_tid[i], NULL);
	
	allDone = 1;
	
	sem_post(&barber_ready);
	
	pthread_join(barber_tid, NULL);
	
	sem_destroy(&waiting_room);
	sem_destroy(&mutex_chair);
	sem_destroy(&barber_ready);
	sem_destroy(&customer_ready);

	pthread_exit(NULL);
}
