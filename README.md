# Data Structures in C


##Hash table##

This repository currently provides a generic hash table implementation using void pointers.

The main module: **hash_table.c** contains the generic functions of the hash table, including the function **create_hash_table**, which given a pointer to a function that computes the hash values for the keys of the hash table, a pointer to a comparator function and the number of slots, it returns a new heap allocated hash table.

Some of example of hash functions and compartor functions are provided in the module named: **hash_utility_func.c**.

The third module: **hash_table_tests.c** includes usage examples and a **stress test**, designed to verify the hash table on longer periods of time. At each iteration it tries to add a tuple of the form (string, int), with keys randomly generated, to the hash table and delete an already contained tuple. The execution time and the maximum number of tuples in the hash table at a given moment of time are variables and can be modified. You can use the atached makefile to compile and run it.

## Makefile commands:

1. Compile the files and run the executable file named hash_table_tests
```bash
% make
% ./hash_table_tests
```
2. Compile and run the executable (including the stress test), using the valgrind tool to check for memory leaks.
```bash
% make run_tests
```
3. Clean all the binaries

```bash
% make clean
```
