#CS253 PA8 makefile
#Alexander Day

CC=g++
OBJS=main.o Image.o
DEBUG=-g
CFLAGS=-std=c++11 -O2 -Wall -I. -c $(DEBUG)
LFLAGS=-Wall $(DEBUG)

all: pa8

pa8: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o pa8

main.o: main.cpp Image.h
	$(CC) $(CFLAGS) main.cpp

Image.o: Image.cpp Image.h
	$(CC) $(CFLAGS) Image.cpp

clean:
	rm -f $(OBJS) *~ pa8
 

