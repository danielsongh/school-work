CC = gcc
FLAGS = -std=c99 -Wall
LIBS = -lrt -pthread

concurrency.o: conc3.c
	$(CC) $(FLAGS) -c conc3.c $(LIBS)

list.o: list.c list.h
	$(CC) $(FLAGS) -c list.c $(LIBS)

clean: 
	rm -f *.o *.out

all: concurrency.o list.o
	$(CC) $(FLAGS) conc3.o list.o $(LIBS)
	
