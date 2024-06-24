#compile all in src and the headers are in include

# OS detection
ifeq ($(OS),Windows_NT)
	# Windows
	EXECUTABLE = Main.exe
else
	# Linux
	EXECUTABLE = Main
endif

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -std=c99 -Iinclude -O3

# Linker flags
LDFLAGS = -lm

# Source files
SOURCES = $(wildcard src/*.c)

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(EXECUTABLE)

# Linking
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Compilation
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Clean
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	rm -f $(SOURCES:.c=.d)

# Dependencies
-include $(SOURCES:.c=.d)

# Generate dependencies
%.d: %.c
	$(CC) -MM $< -MT $(@:.d=.o) > $@

# Phony targets
.PHONY: all clean

# EOF