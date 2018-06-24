#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
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
  hash_table *string_hash_table = create_hash_table(&string_hash_func, &string_cmp_funct, 100);

  const int RUN_TIME = 24; //number of seconds to run the test
  time_t start_time = time(NULL);

  int dummy_value = 1; //Dummy value to be added to the hash table

  int no_of_strings = 0;
  int no_of_iterations = 0;
  int max_no_of_strings = 1000;
  int str_size;
  char **table_of_strings = (char **) calloc(max_no_of_strings, sizeof(char *)); //Matrix to keep all the keys stored in the hash table

  printf("Started the stress test.\n");
  while(difftime(time(NULL), start_time) < RUN_TIME) {
  //while(no_of_iterations <= 110) {

    if(!no_of_strings) {
      ++no_of_iterations;
      printf("Iteration number: %d\n", no_of_iterations);
    }

    if(no_of_iterations > 1) {
      if(!delete(string_hash_table, *(table_of_strings + no_of_strings))) {
        printf("Node deletion was unsuccessful. The key to be deleted was \"%s\"\n",
               *(table_of_strings + no_of_strings));
        //print_table(string_hash_table, &string_int_printer);
      }
      free(*(table_of_strings + no_of_strings));
    }

    //Creates a new random string and add it to the hash table
    str_size = rand() % 25 + 10; //The size of the string to be generated
    *(table_of_strings + no_of_strings) = (char *) calloc(str_size + 1, sizeof(char));
    gen_random(*(table_of_strings + no_of_strings), str_size);

    add(string_hash_table, *(table_of_strings + no_of_strings), &dummy_value);

    assert(contains(string_hash_table, *(table_of_strings + no_of_strings)));

    no_of_strings = (no_of_strings + 1) % max_no_of_strings;
  }

  //Free the table of strings
  if(no_of_iterations > 1) {
    for (int i = 0; i < max_no_of_strings; ++i) {
      free(*(table_of_strings + i));

    }
  }else {
    for (int i = 0; i < no_of_strings; ++i) {
      free(*(table_of_strings + i));
    }
  }
  free(table_of_strings);

  free_table(string_hash_table);
}

int main() {

  small_test1();
  stress_test();
  return 0;
}