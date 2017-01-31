#CS253 PA10 makefile
#Alexander Day

CC=g++
OBJS=main.o Image.o
CFLAGS=-march=native -std=c++11 -Ofast -Wall -I. -c 
LFLAGS=-Wall

all: pa10

pa10: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o pa10

main.o: main.cpp Image.h
	$(CC) $(CFLAGS) main.cpp

Image.o: Image.cpp Image.h
	$(CC) $(CFLAGS) Image.cpp

clean:
	rm -f $(OBJS) *~ pa10
 

