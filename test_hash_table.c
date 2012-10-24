#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "hash_table_c.h"

#define tableSize 100
linked_list* hash_table[tableSize] = {NULL};

void insert_a_pair() {
	insertPair("string", 25, hash_table, tableSize);
}

void insert_2nd_pair() {
	insertPair("string", 37, hash_table, tableSize);
}

void insert_3rd_pair() {
	insertPair("different_string", 19, hash_table, tableSize);
}

void remove_a_pair() {
	removePair("string", hash_table, tableSize);
}

START_TEST(test_insert) {
	//2 pairs are inserted into the hash table
	//with the same key parts(just to make sure they are in the same list) 
	//but different value parts. Then its tested whether they are property inserted.	
	
	insert_a_pair();
	linked_list* head = (linked_list *)hash_table[f("string", tableSize)];
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

	insert_a_pair();
	insert_2nd_pair();
	remove_a_pair();
	
	linked_list* head = (linked_list *)hash_table[f("string", tableSize)];
	fail_unless(head == NULL, "Bucket is not empty");
}
END_TEST

START_TEST(test_get) {
	//a pair is inserted into the table and then
	//retrieved.

	insert_3rd_pair();

	keyValue *tmp = getPair("different_string", hash_table, tableSize);
	fail_unless(strcmp(tmp->key, "different_string") == 0 && tmp->value == 19, "Problem with getting the pair");
}
END_TEST

Suite* hash_table_suite(void) {
	Suite *s = suite_create("Hash_Table");
	
	TCase *ht_case = tcase_create("HT_case");
	tcase_add_test(ht_case, test_insert);
	tcase_add_test(ht_case, test_remove);
	tcase_add_test(ht_case, test_get);
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
