#ifndef HASH_HASH_TABLE_H
#define HASH_HASH_TABLE_H
#define STANDARD_NO_OF_SLOTS 93323

#include <stdbool.h>

/**
 * The hash value returned is then divided by the maximum number
 * of slots inside internal functions of the hash table.
 *
 * @param key
 * @return an integer representing the hash value for the given key.
 */
typedef __uint32_t (*hash_funct_ptr)(void *);

/**
 * @param pointer to first key
 * @param pointer to second key
 * @return negative value if key1 "<" ke2, 0 if key1 "=" key2 and a positive value otherwise
 */
typedef int (*comparator_funct_ptr)(void *, void *);

/**
 * Prints a hash table pair to the standard output. It assumes the hash_table pairs have all the same type.
 *
 * @param pointer to the key
 * @param pointer to the value
 */
typedef void(*print_funct)(void *, void *);

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


/**
 * @brief Verifies the key is contained by the hash table
 *
 * Verifies if the provided hash table contains the given key
 * and it returns true if that is the case, false otherwise.
 *
 * @param table The hash table to search in
 * @param key The key to search for
 * @return true if the key is contained by the hash table, false otherwise
 */
bool contains(hash_table *table, void *key);

/**
 * @brief It adds a tuple of the form (key, value) to the hash table.
 *
 * Tries to add the given tuple to the hash table,
 * it return true on success and false otherwise.
 * If the key is already stored in the hash table,
 * it does not update the value.
 *
 * @param table The hash table to add to
 * @param key The key for the tuple to be added
 * @param value The value for the tuple to be added
 * @return True if the tuple was added successfully, false otherwise.
 */
bool add(hash_table *table, void *key, void *value);

/**
 * @brief It deletes the tuple determined by the given key from the hash table.
 *
 * Tries to delete the the tuple determined by the given key from the hash table,
 * it return true on success and false otherwise.
 *
 * @param table The hash table to delete from
 * @param key The key that uniquely determines the tuple to be deleted
 * @return True if the tuple was deleted successfully, false otherwise.
 */
bool delete(hash_table *table, void *key);

/**
 * @brief Returns the value of the tuple determined by the given key
 *
 * Returns the value of the tuple determined
 * by the given key in the form of a void *.
 * If there is no tuple with that key it return NULL.
 *
 * @param table The hash table to search in
 * @param key The key to search for
 * @return Returns the value of the tuple, NULL if the tuple does not exist
 */
void *get_value(hash_table *table, void *key);


/**
 * Frees all the memory allocated for the hash table.
 * @param table The hash table that will be freed.
 */
void free_table(hash_table *table);

/**
 * @brief Creates a new hash table.
 *
 * Creates a new hash table that uses as its hash function
 * the one specified as an argument. The same is true for
 * the comparator function used to determine the order of
 * elements in case of slots collisions and for the number
 * of slots.
 * It stops the program is the memory allocation failed.
 *
 * @param hash_function A pointer to a function that
 * computes the slot position for a given key
 *
 * @param cmp_func A pointer to a function that compares two
 * different keys as specified for the comparator_funct_ptr typedef
 *
 * @param no_of_slots The number of slots of the new table
 *
 * @return A pointer to the new hash table.
 */
hash_table *create_hash_table(hash_funct_ptr hash_function, comparator_funct_ptr cmp_func, __uint32_t no_of_slots);


/**
 * @brief Prints the entire content of the provided hash table
 *
 * It prints all the tuples contained by the given hash table,
 * using for each individual tuple the provided print function.
 * This function takes as argument the tuple to be printed,
 * as two void * pointers.
 *
 * Important: It assumes that all the tuples in the hash table
 * have the same type.
 *
 * @param table The hash table to be printed
 * @param printer Pointer to a print function
 */
void print_table(hash_table *table, print_funct printer);

#endif //HASH_HASH_TABLE_H
