#include "hash_utility_func.h"
#include "stdio.h"


/* Hash And comparator function for int keys */
int int_hash_func(void *key) {
  return *((int *)key) % STANDARD_NO_OF_SLOTS;
}

int int_cmp_funct(void *key1, void *key2) {
  if(*((int *)key1) == *((int *)key2)) {
    return 0;
  }

  return (*((int *)key1) < *((int *)key2)) ? -1 : 1;
}

/* Printer function for (int, string) pairs */
void int_string_printer(void *key, void *value) {

  int int_key = *((int *)key);
  char *str   = ((char *)value);

  printf("( %d, '%s' )", int_key, str);
}
