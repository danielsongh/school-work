CC = gcc
CFLAGS = -Wall -std=c99
INCLUDES  = 
LIBS = -pthread
SRCS = buffer.c concurrency1.c


concurrency.o: concurrency1.c buffer.c
	$(CC) $(CFLAGS) -c $(LIBS) concurrency1.c 

buffer.o: buffer.c buffer.h
	$(CC) $(CFLAGS) -c $(LIBS) buffer.c

clean:
	rm -f *.o *.out

all: concurrency.o buffer.o
	$(CC) $(CFLAGS) -o app concurrency1.o buffer.o



