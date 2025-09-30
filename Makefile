# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11  # Warnings and C standard
LDFLAGS = -L.  # Library search path (current directory)

# Library name and objects
LIBRARY = libadd.a
LIB_OBJS = add.o

# Test program
TARGET = test
SOURCES = test.c

# Default target: build everything
all: $(LIBRARY) $(TARGET)

# Rule to build the static library
$(LIBRARY): $(LIB_OBJS)
	ar rcs $@ $^

# Rule to compile object files (generic for any .c to .o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link the test program
$(TARGET): $(SOURCES) $(LIBRARY)
	$(CC) $(SOURCES) $(LDFLAGS) -ladd -o $@

# Clean up generated files
clean:
	rm -f $(LIB_OBJS) $(LIBRARY) $(TARGET)

# Phony targets (not actual files)
.PHONY: all clean
