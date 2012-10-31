#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "hash_table.h"
#include "hash_table_low.h"
#include "linked_list.h"

hashTable hTable;

void create_a_table() {
	hTable = createTable();
}

void insert_a_pair() {
	addPair("string", 25, &hTable);
}

void insert_2nd_pair() {
	addPair("string", 37, &hTable);
}

void remove_a_pair() {
	deletePair("string", &hTable);
}

void insert_many() {
	addPair("a", 25, &hTable);
	addPair("b", 25, &hTable);
	addPair("c", 25, &hTable);
	addPair("d", 25, &hTable);
	//addPair("e", 25, &hTable);
	//addPair("f", 25, &hTable);
	//addPair("g", 25, &hTable);
	//addPair("h", 25, &hTable);
}

START_TEST(test_create) {
	//creates a hash table and tests its
	//initial parameters
	
	create_a_table();
	
	fail_unless(hTable.table != NULL, "Problem creating a hash table");
	fail_unless(hTable.tableSize == 5, "Problem with the size of table");
	fail_unless(hTable.loadFactor == 0, "Problem with the load factor of table");
	fail_unless(hTable.maxLoad == 0.75, "Problem with the max load of table");
	fail_unless(hTable.minLoad == 0.25, "Problem with the min load of table");
	
}
END_TEST

START_TEST(test_add) {
	//2 pairs are inserted into the hash table
	//with the same key parts(just to make sure they are in the same list) 
	//but different value parts. Then its tested whether they are property inserted.	
	
	create_a_table();

	insert_a_pair();
	linked_list* head = (linked_list *) hTable.table[f("string", hTable.tableSize)];
	fail_unless(head != NULL, "Bucket is empty");
	
	char* tmp_key = (head->data)->key;
	int tmp_value = (head->data)->value;
	fail_unless(strcmp("string", tmp_key) == 0 && tmp_value == 25, "Problem with the first insertion");
	
	insert_2nd_pair();
	tmp_key = (head->data)->key;
	tmp_value = (head->data)->value;

	fail_unless(strcmp("string", tmp_key) == 0 && tmp_value == 37, "Problem with the second insertion");
	
}
END_TEST

START_TEST(test_remove) {
	//2 pairs are inserted into the hash table
	//then one pair is removed. Its tested whether the pair
	//is removed successfully and the second pair is at the head
	//of the corresponding list.
	
	create_a_table();

	insert_a_pair();
	insert_2nd_pair();
	remove_a_pair();
	
	linked_list* head = (linked_list *) hTable.table[f("string", hTable.tableSize)];
	fail_unless(head == NULL, "Bucket is not empty");
}
END_TEST

START_TEST(test_resize) {
	//
	
	create_a_table();

	insert_many();
	
	printf("load factor -> %f\n", hTable.loadFactor);

	int i;
	for(i=0; i < hTable.tableSize; i++) {
		printf("%d\n", hTable.table[i]);
	}
	
	fail_unless(hTable.tableSize != 5, "not resized");
}
END_TEST

Suite* hash_table_suite(void) {
	Suite *s = suite_create("Hash_Table");
	
	TCase *ht_case = tcase_create("HT_case");
	tcase_add_test(ht_case, test_create);
	tcase_add_test(ht_case, test_add);
	//tcase_add_test(ht_case, test_remove);
	tcase_add_test(ht_case, test_resize);
	suite_add_tcase(s, ht_case);

	return s;
}

int main(void){
	int fail_num;
	Suite *s = hash_table_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	fail_num = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (fail_num == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
