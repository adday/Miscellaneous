# Makefile template for CS 270 (specialized for R12)

# List of files
C_SRCS		= pointers.c
C_OBJS		= pointers.o

OBJS		= ${C_OBJS}
EXE		= R12

# Compiler and loader commands and flags
CC		= c99
CC_FLAGS	= -g -Wall -c
LD_FLAGS	= -g -Wall

# Target is the executable
R12: $(OBJS)
	@echo "Linking all object modules"
	$(CC) $(LD_FLAGS) $(OBJS) -o $(EXE)

# Compile .c files to .o files
.c.o:
	@echo "Compiling each C source file separately"
	$(CC) $(CC_FLAGS) $<

# Clean up the directory
clean:
	@echo "Cleaning up project directory"
	rm -f *.o *~ $(EXE)
