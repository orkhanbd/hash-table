#include "linked_list.h"

typedef struct hashTable {
	linked_list** table;		// linked_list* table[]; ???
	int tableSize;
	double loadFactor;
	double maxLoad;
	double minLoad;
} hashTable;			// problem???

// this function creates a hash table by allocating space in the memory. it returns the hashTable datatype created
hashTable createTable();

// this functon modifies the table. it inserts the key-value pair to the table
void addPair(char* key, int value, hashTable* hTable);

// this function modifies the table. it removes the key-value pair from the table corresponding to the'key'
void deletePair(char *key, hashTable* hTable);
