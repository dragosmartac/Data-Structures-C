#ifndef HASH_HASH_CMP_FUNCTIONS_H
#define HASH_HASH_CMP_FUNCTIONS_H

#define STANDARD_NO_OF_SLOTS 93323

/*Functions for int*/
int int_hash_func(void *key);
int int_cmp_funct(void *key1, void *key2);

/* Printer function for (int, string) pairs */
void int_string_printer(void *key, void *value);

#endif //HASH_HASH_CMP_FUNCTIONS_H
