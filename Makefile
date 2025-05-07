# Makefile for Student Grade Management System
CC = gcc
CFLAGS = -Wall -Wextra -g

# Objects
MAIN_OBJ = main.o
TEST_OBJ = test.o

# Executables
MAIN_EXEC = grade_system
TEST_EXEC = test_suite

# Default target
all: $(MAIN_EXEC)

# Build the main program
$(MAIN_EXEC): $(MAIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Build the test program
$(TEST_EXEC): $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile main.c to object file
main.o: main.c
	$(CC) $(CFLAGS) -c $<

# Compile test.c to object file
test.o: test.c
	$(CC) $(CFLAGS) -c $<

# Run the main program
run: $(MAIN_EXEC)
	./$(MAIN_EXEC)

# Run tests
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Clean up
clean:
	rm -f *.o $(MAIN_EXEC) $(TEST_EXEC)
	rm -f *.csv

# Phony targets (targets that don't represent files)
.PHONY: all clean test run