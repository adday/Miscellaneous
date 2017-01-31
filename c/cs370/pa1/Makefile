#PA1 makefile

CC=gcc
OBJS=PA1.o
DEBUG=-g
CFLAGS=-Wall -I. -c $(DEBUG)
LFLAGS=-Wall $(DEBUG)

all: PA1

PA1: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o PA1

PA1.o: PA1.c 
	$(CC) $(CFLAGS) PA1.c

clean:
	rm -f $(OBJS) *~ 

