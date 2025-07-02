# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Source files
SRC = $(wildcard test[1-8].c)

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
