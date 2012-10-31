#include "linked_list.h"

// this function modifies the hash table. insert the key value pair into the hash table
double insertPair(char* key, int value, linked_list** table, int tableSize, double loadFactor);

// this function modifies the hash table. removes the key value pair with key 'key' from the hash table
double removePair(char* key, linked_list** table, int tableSize, double loadFactor);

// this function returns a pointer to the keyValue element with key 'key' stored in the hash table
keyValue* getPair(char* key, linked_list** table, int tableSize);

// this function modifies the hash table. it doubles the table size and rehashes all its content
linked_list** doubleSize(linked_list** table, int tableSize, double loadFactor);

// this function modifies the hash table. it halves the table size and rehashes all its content
linked_list** halveSize(linked_list** table, int tableSize, double loadFactor);
