# Makefile for hello.s
# Usage: make (builds hello), make clean (removes build files)

# Default target: build the executable
all: hello

# Link object file to executable
hello: hello.o
	ld hello.o -o hello

# Assemble source to object file
hello.o: hello.s
	as -64 hello.s -o hello.o

# Clean up generated files
clean:
	rm -f hello.o hello

# Phony targets (not actual files)
.PHONY: all clean
