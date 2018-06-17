CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

.SUFFIXES: .c .o

.PHONY: all clean

all: hash_table_tests

run_tests: 	hash_table_tests
		valgrind --tool=memcheck --leak-check=yes ./hash_table_tests

hash_table_tests: hash_table.o hash_utility_func.o

hash_table.o: hash_table.h

hash_utility_funct.o: hash_utility_func.h

clean:
	rm -f $(wildcard *.o)
	rm -f hash_table_tests


