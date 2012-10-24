#include "linked_list.h"

// this function modifies the hash table. insert the key value pair into the hash table
void insertPair(char* key, int value, linked_list* table[], int tableSize);

// this function modifies the hash table. removes the key value pair with key 'key' from the hash table
void removePair(char* key, linked_list* table[], int tableSize);

// this function returns a pointer to the keyValue element with key 'key' stored in the hash table
keyValue* getPair(char* key, linked_list* table[], int tableSize);

// this function prints all the key value pairs stored in the hash table
void printAllTable(linked_list* table[], int tableSize);
