#include <stdio.h>
#include <stdlib.h>
#include "hash_table_low.h"
#include "linked_list.h"

double insertPair(char* key, int value, linked_list** table, int tableSize, double loadFactor) {
	keyValue* data;
	linked_list* tmp;
	double newLoadFactor = loadFactor;	
	
	data = (keyValue *)malloc(sizeof(keyValue));
	data->key = key;
	data->value = value;

	int hash = f(key, tableSize);
	tmp = find(key, table[hash]);

	if(tmp == NULL){
		if(table[hash] != NULL)
			add(data, table[hash]);
		else
			table[hash] = initiate(data);

		newLoadFactor = (loadFactor*tableSize + 1) / tableSize;
	}
	else{
		(tmp->data)->value = value;
	}

	return newLoadFactor;
}

double removePair(char* key, linked_list** table, int tableSize, double loadFactor) {
	linked_list* tmp;

	int hash = f(key, tableSize);
	double newLoadFactor = loadFactor;
	tmp = find(key, table[hash]);
	
	if(tmp != NULL) {
		table[hash] = removeData(key, table[hash]);
		newLoadFactor = (loadFactor*tableSize - 1) / tableSize;
	}

	return newLoadFactor;
}

keyValue* getPair(char* key, linked_list** table, int tableSize) {
	keyValue* data;
	data = NULL;
	int hash = f(key, tableSize);
	
	if(table[hash] != NULL)
		data = find(key, table[hash])->data;

	return data;
}

linked_list** doubleSize(linked_list** table, int tableSize, double loadFactor) {
	linked_list** newTable;
	int newTableSize = tableSize * 2;
	double newLoadFactor = loadFactor / 2;
	newTable = (linked_list**) calloc(newTableSize, sizeof(linked_list*));
	
	int i;
	for(i=0; i < tableSize; i++) {
		while(table[i] != NULL){
			insertPair((table[i]->data)->key, (table[i]->data)->value, newTable, newTableSize, newLoadFactor);
			removePair((table[i]->data)->key, table, tableSize, loadFactor);
		}
	}
	free(table);
	
	return newTable;
}

linked_list** halveSize(linked_list** table, int tableSize, double loadFactor) {
	linked_list** newTable;
	int newTableSize = tableSize / 2;
	double newLoadFactor = loadFactor * 2;
	newTable = (linked_list**) calloc(newTableSize, sizeof(linked_list*));
	
	int i;
	for(i=0; i < tableSize; i++) {
		while(table[i] != NULL){
			insertPair((table[i]->data)->key, (table[i]->data)->value, newTable, newTableSize, newLoadFactor);
			removePair((table[i]->data)->key, table, tableSize, loadFactor);
		}
	}
	free(table);
	
	return newTable;
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
