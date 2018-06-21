#include <stdio.h>
#include "hash_table.h"
#include "hash_utility_func.h"

void small_test1() {
  hash_table *int_hash_table = create_hash_table(&int_hash_func, &int_cmp_funct, STANDARD_NO_OF_SLOTS);

  /*Test keys*/
  int int_list[] = {111, 223, 423, 223, STANDARD_NO_OF_SLOTS * 2 + 111, 111, STANDARD_NO_OF_SLOTS + 111};

  /*Test values*/
  char *str1 = "test1";
  char *str2 = "test2";
  char *str3 = "test3";

  add(int_hash_table, int_list, str1);
  add(int_hash_table, int_list + 1, str2);
  add(int_hash_table, int_list + 2, str3);

  printf("Contains %d, result %d\n", int_list[0], contains(int_hash_table, int_list));      // 111
  printf("Contains %d, result %d\n", int_list[5], contains(int_hash_table, int_list + 5));  // 111
  printf("Contains %d, result %d\n", int_list[1], contains(int_hash_table, int_list + 1));  // 223
  printf("Contains %d, result %d\n", int_list[2], contains(int_hash_table, int_list + 2));  // 423

  delete(int_hash_table, int_list);

  printf("Contains %d, result %d\n", int_list[0], contains(int_hash_table, int_list));      // 111
  printf("Contains %d, result %d\n", int_list[5], contains(int_hash_table, int_list + 5));  // 111

  add(int_hash_table, int_list, str1);
  add(int_hash_table, int_list + 4, str1);
  add(int_hash_table, int_list + 6, str1);

  printf("\nTesting get_value function:\n");
  printf("The key %d, contains %s\n", int_list[0], (char *)get_value(int_hash_table, int_list));
  printf("The key %d, contains %s\n", int_list[1], (char *)get_value(int_hash_table, int_list + 1));
  printf("The key %d, contains %s\n", int_list[4], (char *)get_value(int_hash_table, int_list + 4));

  printf("\n");

  print_table(int_hash_table, int_string_printer);


  free_table(int_hash_table);

}

int main() {

  small_test1();

  return 0;
}