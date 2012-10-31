#include <stdio.h>
#include <stdlib.h>
#include "hash_table_low.h"
#include "linked_list.h"
#include "hash_table.h"

hashTable createTable() {
	hashTable hTable;

	hTable.tableSize = 10;
	hTable.loadFactor = 0;
	hTable.maxLoad = 0.75;
	hTable.minLoad = 0.25;
	
	hTable.table = (linked_list**) calloc(hTable.tableSize, sizeof(linked_list*));

	return hTable;
}

void addPair(char* key, int value, hashTable* hTable) {
	hTable->loadFactor = insertPair(key, value, hTable->table, hTable->tableSize, hTable->loadFactor);

	if(hTable->loadFactor > hTable->maxLoad) {
		hTable->table = doubleSize(hTable->table, hTable->tableSize, hTable->loadFactor);
		hTable->loadFactor = hTable->loadFactor / 2;
	}
}

void deletePair(char* key, hashTable* hTable) {
	hTable->loadFactor = removePair(key, hTable->table, hTable->tableSize, hTable->loadFactor);

	if(hTable->loadFactor < hTable->minLoad && hTable->tableSize > 1) {
		hTable->table = halveSize(hTable->table, hTable->tableSize, hTable->loadFactor);
		hTable->loadFactor = hTable->loadFactor * 2;
	}
}
