#include <stdio.h>
#include <stdlib.h>
#include "hash_table_c.h"
#include "linked_list.h"

void insertPair(char* key, int value, linked_list* table[], int tableSize) {
	keyValue* data;
	data = (keyValue *)malloc(sizeof(keyValue));
	data->key = key;
	data->value = value;

	int hash = f(key, tableSize);			//hash function
	if(table[hash] != NULL)
		add(data, table[hash]);
	else
		table[hash] = initiate(data);
}

void removePair(char* key, linked_list* table[], int tableSize) {
	int hash = f(key, tableSize);			//hash function
	
	if(table[hash] != NULL)
		table[hash] = removeData(key, table[hash]);
}

keyValue* getPair(char* key, linked_list* table[], int tableSize) {
	keyValue* data;
	data = NULL;
	int hash = f(key, tableSize);			//hash function
	
	if(table[hash] != NULL)
		data = find(key, table[hash])->data;

	return data;
}

int f(char* key, unsigned tableSize){
	int hashVal = 0;
	int x;
	for (x = 0; x < sizeof(key); ++x){
		hashVal ^= (hashVal << 5) +
		(hashVal >> 2) +
		key[x];
	}
	
	return hashVal % tableSize;
}
