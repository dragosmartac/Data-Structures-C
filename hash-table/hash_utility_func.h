#ifndef HASH_HASH_CMP_FUNCTIONS_H
#define HASH_HASH_CMP_FUNCTIONS_H

#include <stdio.h>

/*Functions for int keys*/
__uint32_t int_hash_func(void *key);
int int_cmp_funct(void *key1, void *key2);

/*Functions for string keys*/
__uint32_t string_hash_func(void *key);
int string_cmp_funct(void *key1, void *key2);

/* Printer function for (int, string) pairs */
void int_string_printer(void *key, void *value);
/*Printer function for (string, int) pairs*/
void string_int_printer(void *key, void *value);


#endif //HASH_HASH_CMP_FUNCTIONS_H
