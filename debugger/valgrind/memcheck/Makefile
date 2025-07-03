# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -O0

# Source files
SRC = $(wildcard test[1-9].c) test10.c

# Executables (strip .c)
EXE = $(SRC:.c=)

# Default target: build all
all: $(EXE)

# Rule to build each executable
%: %.c
	$(CC) $(CFLAGS) $< -o $@

# Clean rule
clean:
	rm -f $(EXE)
