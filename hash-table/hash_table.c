#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

void error_check(hash_table *table,
                 char *func_name) {
  if(table == NULL) {
    perror(strcat("Provided table is null. Error appeared in ", func_name));
    exit(EXIT_FAILURE);
  }
  if(table->slots_list == NULL) {
    perror(strcat("Provided table has an empty list of slots. Error appeared in ", func_name));
    exit(EXIT_FAILURE);
  }
  if(table->hash_function == NULL) {
    perror(strcat("Provided hash function pointer is null. Error appeared in ", func_name));
    exit(EXIT_FAILURE);
  }
  if(table->cmp_func == NULL) {
    perror(strcat("Provided comparator function pointer is null. Error appeared in ", func_name));
    exit(EXIT_FAILURE);
  }
}

hash_node *new_hash_node(void *key, void *value) {
  hash_node *node = malloc(sizeof(hash_node));

  if(node == NULL) {
    perror("Node allocation failed in new_hash_node.");
    exit(EXIT_FAILURE);
  }

  node->key = key;
  node->value = value;
  node->next = NULL;

  return node;
}

bool contains(hash_table *table, void *key) {

  /*Check the given arguments*/
  error_check(table, "contains function.");
  if(key == NULL) {
    perror("Provided key pointer is null. Error appeared in contains function.");
    exit(EXIT_FAILURE);
  }

  int slot = table->hash_function(key) % table->no_of_slots;

  hash_node *curr = table->slots_list[slot];

  while(curr != NULL && table->cmp_func(curr->key, key) <= 0) {
    if(!table->cmp_func(curr->key, key)) {
      return true;
    }
    curr = curr->next;
  }

  return false;
}

bool add(hash_table *table, void *key, void *value) {

  /*Check the given arguments*/
  error_check(table, "add function.");
  if(key == NULL) {
    perror("Provided key pointer is null. Error appeared in add function.");
    exit(EXIT_FAILURE);
  }

  int slot = table->hash_function(key) % table->no_of_slots;

  hash_node *curr = table->slots_list[slot];
  hash_node *prev = NULL;

  while(curr != NULL && table->cmp_func(curr->key, key) <= 0) {
    if(!table->cmp_func(curr->key, key)) {
      return false;
    }
    prev = curr;
    curr = curr->next;
  }

  hash_node *new_node = new_hash_node(key, value);
  if(prev == NULL) {
    table->slots_list[slot] = new_node;
  }else {
    prev->next = new_node;
    new_node->next = curr;
  }

  return true;

}

bool delete(hash_table *table, void *key) {

  /*Check the given arguments*/
  error_check(table, "delete function.");
  if(key == NULL) {
    perror("Provided key pointer is null. Error appeared in delete function.");
    exit(EXIT_FAILURE);
  }

  int slot = table->hash_function(key) % table->no_of_slots;

  hash_node *curr = table->slots_list[slot];
  hash_node *prev = NULL;

  while(curr != NULL && table->cmp_func(curr->key, key) < 0) {
    prev = curr;
    curr = curr->next;
  }
  if(curr == NULL || table->cmp_func(curr->key, key)) {
    return false;
  }

  if(prev == NULL) {
    table->slots_list[slot] = curr->next;
  }else {
    prev->next = curr->next;
  }

  free(curr);

  return true;
}

void *get_value(hash_table *table, void *key) {

  /*Check the given arguments*/
  error_check(table, "get_value function.");
  if(key == NULL) {
    perror("Provided key pointer is null. Error appeared in get_value function.");
    exit(EXIT_FAILURE);
  }

  int slot = table->hash_function(key) % table->no_of_slots;

  hash_node *curr = table->slots_list[slot];

  while(curr != NULL && table->cmp_func(curr->key, key) <= 0) {
    if(!table->cmp_func(curr->key, key)) {
      return curr->value;
    }
    curr = curr->next;
  }

  return NULL;
}

void free_table(hash_table *table) {
  error_check(table, "free_table function.");

  hash_node *node, *next_node;

  for(int i = 0; i < table->no_of_slots; ++i) {
    node = table->slots_list[i];
    while(node != NULL) {
      next_node = node->next;
      free(node);
      node = next_node;
    }
  }

  free(table->slots_list);
  free(table);
}

hash_table *create_hash_table(hash_funct_ptr hash_function, comparator_funct_ptr cmp_func, __uint32_t no_of_slots) {

  /*Check the given arguments*/
  if(hash_function == NULL) {
    perror("Provided hash function pointer is null. Error appeared in create_hash_table.");
    exit(EXIT_FAILURE);
  }
  if(cmp_func == NULL) {
    perror("Provided comparator function pointer is null. Error appeared in create_hash_table.");
    exit(EXIT_FAILURE);
  }

  hash_table *new_hash_table = malloc(sizeof(hash_table));

  if(new_hash_table == NULL) {
    perror("Table allocation failed in new_hash_table.");
    exit(EXIT_FAILURE);
  }

  new_hash_table->slots_list = calloc(no_of_slots, sizeof(hash_node *));

  if(new_hash_table->slots_list == NULL) {
    perror("Slots allocation failed in new_hash_table.");
    exit(EXIT_FAILURE);
  }

  new_hash_table->cmp_func = cmp_func;
  new_hash_table->hash_function = hash_function;
  new_hash_table->no_of_slots = no_of_slots;

  return new_hash_table;
}

void print_table(hash_table *table, print_funct printer) {

  error_check(table, "print_table function.");

  bool has_printed = false;
  bool non_empty_slot;

  hash_node *node;
  for(int i = 0; i < table->no_of_slots; ++i) {
    node = table->slots_list[i];
    non_empty_slot = false;

    if(node != NULL) {
      non_empty_slot = true;
      if(!has_printed) {
        has_printed = true;
        printf("Elements of the hash table:\n");
      }
      printf("table->slots_list[ %d ]: ", i);
    }

    while(node != NULL) {
      printer(node->key, node->value);
      printf(" ");
      node = node->next;
    }

    if(non_empty_slot) {
      printf("\n");
    }
  }

  if(!has_printed) {
    printf("Hash table is empty.");
  }
}