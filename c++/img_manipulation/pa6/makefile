#CS253 PA6 makefile
#Alexander Day

CC=g++
OBJS=main.o Image.o
DEBUG=-g
CFLAGS=-std=c++11 -Wall -I. -c $(DEBUG)
LFLAGS=-Wall $(DEBUG)

all: pa6

pa6: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o pa6

main.o: main.cpp Image.h
	$(CC) $(CFLAGS) main.cpp

Image.o: Image.cpp Image.h
	$(CC) $(CFLAGS) Image.cpp

clean:
	rm -f $(OBJS) *~ pa6
 

