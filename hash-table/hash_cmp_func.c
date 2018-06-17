#include "hash_cmp_func.h"
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
