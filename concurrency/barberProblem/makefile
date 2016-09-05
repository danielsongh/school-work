CC = gcc
FLAGS = -std=c99 -Wall
LIBS = -lrt -pthread


concurrency2.o: p2.c
	$(CC) $(FLAGS) -c p2.c $(LIBS)

clean: 
	rm -f *.o *.out

all: concurrency2.o
	$(CC) $(FLAGS) p2.o $(LIBS)
	
