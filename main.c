#include <stdio.h>
#include "hash_table.h"
#include "hash_cmp_func.h"

int main() {
  hash_table *int_hash_table = create_hash_table(&int_hash_func, &int_cmp_funct, STANDARD_NO_OF_SLOTS);

  /*Test keys*/
  int int_list[] = {1,5,243,24,21,3,54,5,4,3,321,3214215,5,243,523,5,52325,9,97,86,76834,3,3};

  /*Test values*/
  char *str1 = "test1";
  char *str2 = "test2";
  char *str3 = "test3";

//  add(int_hash_table, int_list, str1);
  add(int_hash_table, int_list + 1, str1);
  add(int_hash_table, int_list + 2, str2);
  add(int_hash_table, int_list + 3, str3);

  for(int i = 4; i < 10; ++i) {
    add(int_hash_table, int_list + i, int_list + i);
  }

  for(int i = 0; i < 20; ++i) {
    printf("Contains %d, result %d\n", i, contains(int_hash_table, int_list + i));
  }

  return 0;
}