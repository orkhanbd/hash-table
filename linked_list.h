#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct keyValue{
	char* key;
	int value;
}keyValue; 

typedef struct linked_list{
	keyValue* data;
	struct linked_list* next;
}linked_list;

// this function innitiates the linked list by creating its first element
linked_list* initiate(keyValue* data);

// this function modifies the list. replaces or adds an element to the end of the linked list
void add(keyValue* data, linked_list* list);

// this function modifies the list. remove the first element from the list who's value equals 'value'
linked_list* removeData(char* key, linked_list* list);

// return the pointer to the element who's value equals 'value'. Return NULL if no such element is found.
linked_list* find(char* key, linked_list* list);

// return the first element in the list
linked_list* getFirst(linked_list* list);

// return the last element in the list
linked_list* getLast(linked_list* list);

// get the element at the index 'index' in the list. return NULL if index overflows.
linked_list* get(int index, linked_list* list);

// this function modifies the list. remove the element at the index 'index'. do nothing if index overflows.
linked_list* removeAtIndex(int index, linked_list* list);

// this function modifies the list. reverse the list such that the element in the end of the list becomes the head of the list.
linked_list* reverseList(linked_list* list);

// this function prints all the elements of the linked list in the order of insertion
void printAll(linked_list *list); 

#endif
