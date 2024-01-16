# Makefile for MPI programs

# Compiler
CC = mpicc

# Compiler flags
CFLAGS = -Wall

# Target executable names
TARGET1 = monte-carlo.run
TARGET2 = integral.run

# Source files
SRC1 = ./mpi-monte-carlo.c
SRC2 = ./mpi-integral.c

# Default target
all: $(TARGET1) $(TARGET2)

$(TARGET1): $(SRC1)
	$(CC) $(CFLAGS) -o $(TARGET1) $(SRC1)

$(TARGET2): $(SRC2)
	$(CC) $(CFLAGS) -o $(TARGET2) $(SRC2)

# Clean target to remove executables and object files
clean:
	rm -f $(TARGET1) $(TARGET2)

.PHONY: all clean

