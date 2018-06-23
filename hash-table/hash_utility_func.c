#include <string.h>
#include "hash_utility_func.h"


/* Hash And comparator function for int keys */
__uint32_t int_hash_func(void *key) {
  return *((__uint32_t *)key);
}

int int_cmp_funct(void *key1, void *key2) {
  if(*((int *)key1) == *((int *)key2)) {
    return 0;
  }

  return (*((int *)key1) < *((int *)key2)) ? -1 : 1;
}

/*Hash function and comparator function fot string keys*/
__uint32_t string_hash_func(void *key) {
  char *str = (char *)key;
  __uint32_t hash_value = 0;
  while (*str) {
    hash_value = (hash_value << 5) + hash_value + *str;
    ++str;
  }

  return hash_value;
}

int string_cmp_funct(void *key1, void *key2) {
  char *str1 = (char *)key1;
  char *str2 = (char *)key2;

  return strcmp(str1, str2);
}

/* Printer function for (int, string) pairs */
void int_string_printer(void *key, void *value) {

  int int_key = *((int *)key);
  char *str   = ((char *)value);

  printf("( %d, '%s' )", int_key, str);
}

/*Printer function for (string, int) pairs*/
void string_int_printer(void *key, void *value) {

  char *str   = ((char *)key);
  int int_value = *((int *)value);

  printf("( %s, '%d' )", str, int_value);
}