# Compiler and flags
CC = gcc
CFLAGS = -O2 -g -Wall -Iadd -Ihello -Itime -Igelb  # Warnings, GNU C11 (enables asm), include paths for both libs
LDFLAGS = -Ladd -Lhello -Ltime -Lgelb # Library search path (subdirs where libs are)

# Library names and objects (for both add and hello)
LIBRARIES = add/libadd.a hello/libhello.a time/libtime.a gelb/libgelb.a
LIB_OBJS = add/add.o hello/hello.o time/time.o gelb/gelb.o

# Test program
TARGET = test
SOURCES = test.c

# Default target: build everything
all: $(LIBRARIES) $(TARGET)

# Rules to build static libraries
add/libadd.a: add/add.o
	ar rcs $@ $^
hello/libhello.a: hello/hello.o
	ar rcs $@ $^
time/libtime.a: time/time.o
	ar rcs $@ $^
gelb/libgelb.a: gelb/gelb.o
	ar rcs $@ $^

# Rule to compile object files (generic for any .c to .o in subdirs)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link the test program (against both libraries)
$(TARGET): $(SOURCES) $(LIBRARIES)
	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) -ladd -lgelb -lhello -ltime -o $@

# Clean up generated files from both subdirs
clean:
	rm -f $(LIB_OBJS) $(LIBRARIES) $(TARGET)

# Phony targets (not actual files)
.PHONY: all clean