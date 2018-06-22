#include <stdio.h>
#include <time.h>
#include <stdlib.h>
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

void gen_random(char *s, const int len) {
  static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

  for (int i = 0; i < len; ++i) {
    s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
  }

  s[len] = 0;
}

void stress_test() {

  //Create a hash table for tuples of the form (string, int)
  hash_table *string_hash_table = create_hash_table(&string_hash_func, &string_cmp_funct, STANDARD_NO_OF_SLOTS);

  const int RUN_TIME = 120; //number of seconds to run the test
  time_t start_time = time(NULL);

  int dummy_value = 1; //Dummy value to be added to the hash table

  int no_of_strings = 0;
  int max_no_of_strings = 30000;
  char **table_of_strings = (char **) malloc(max_no_of_strings * sizeof(char *)); //Matrix to keep all the keys stored in the hash table

  while(difftime(start_time, time(NULL)) < RUN_TIME) {

    //Creates a new random string and add it to the hash table
    int str_size = rand() % 25; //The size of the string to be generated
    *(table_of_strings + no_of_strings) = (char *) calloc(str_size, sizeof(char));
    gen_random(*(table_of_strings + no_of_strings), str_size);

    add(string_hash_table, *(table_of_strings + no_of_strings), &dummy_value);
  }

}

int main() {

  small_test1();

  return 0;
}