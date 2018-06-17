#ifndef HASH_HASH_TABLE_H
#define HASH_HASH_TABLE_H

#include <stdbool.h>

/**
 * @param key
 * @return an integer representing the slot index for the given key. (returned index < no_of_slots)
 */
typedef int (*hash_funct_ptr)(void *);

/**
 * @param pointer to first key
 * @param pointer to second key
 * @return negative value if key1 "<" ke2, 0 if key1 "=" key2 and a positive value otherwise
 */
typedef int(*comparator_funct_ptr)(void *, void *);

typedef struct hash_node{
    void *key;
    void *value;
    struct hash_node *next;
}hash_node;

typedef struct  {
    hash_node **slots_list; /*Array of pointers to hash_nodes*/
    hash_funct_ptr hash_function;
    comparator_funct_ptr cmp_func;
    __uint32_t no_of_slots;
}hash_table;

bool contains(hash_table *table, void *key);

bool add(hash_table *table, void *key, void *value);

bool delete(hash_table *table, void *key);

void free_table(hash_table *table);

hash_table *create_hash_table(hash_funct_ptr hash_function, comparator_funct_ptr cmp_func, __uint32_t no_of_slots);

#endif //HASH_HASH_TABLE_H
