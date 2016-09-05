CC = gcc
FLAGS = -std=c99 -Wall
LIBS = -lrt -pthread


concurrency1.o: p1.c
	$(CC) $(FLAGS) -c p1.c $(LIBS)

clean: 
	rm -f *.o *.out

all: concurrency1.o
	$(CC) $(FLAGS) p1.o $(LIBS)
	
