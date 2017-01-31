#simple Makefile for FLOAT Assignment

# these are defined so that on a different system only these definitions
# need to change if c99 and rm are actually in different locations
# The rest of the Makefile need not change

RM   = /bin/rm
CC  = c99

CFLAGS  = -g -Wall -c
LDFLAGS = -g

testFlt32: field.o flt32.o testFlt32.o
	${CC} ${LDFLAGS} -o testFlt32 field.o flt32.o testFlt32.o

flt32.o: field.h flt32.h flt32.c
	${CC} ${CFLAGS} flt32.c

testFlt32.o: field.h flt32.h testFlt32.c
	${CC} ${CFLAGS} testFlt32.c

clean:
	${RM} -f flt32.o testFlt32.o testFlt32


