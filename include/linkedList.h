#ifndef LL_H
#define LL_H

#include <stddef.h>

typedef struct Nodes Node;

typedef struct Nodes {
    void* data;
    Node* next;
} Node;

/**
 * Create a new list.
 * 
 * @param void* data    The data for the first node in the list.
 * @param size_t size   The size of the data.
 * @returns Node*       The head of the list.
*/
Node* create(void* data, size_t size);

/**
 * Destroys a List.
 * 
 * @param List** list    The List to be destroyed.
 * @returns void
*/
void destroy(Node** list);

/**
 * Inserts a Node at the end of a List.
 * 
 * @param List* list    The List to add data to.
 * @param void* data    The data to be appended to the end of the List.
 * @param size_t size   The size of the data.
 * @returns void
*/
void insert(Node* list, void* data, size_t size);

/**
 * Deletes data from a List. This function deletes all matching data from the List, not just the first occurrance.
 * 
 * @param List* list    The List to delete from.
 * @param void* data    The data to delete.
 * @returns void
*/
void delete(Node* list, void* data, int (*cmp)(const void*, const void*));

/**
 * Searches a list.
 * 
 * @param List* list    The list to search.
 * @param void* data    The data to search for.
 * @param int() cmp     The user-defined comparison function to use to compare data in the list. This function must return an integer, 0 for no match and not 0 for a match.
 * @returns Node*       The first Node containing the data in the List, NULL if not present.
*/
Node* search(Node* list, void* data, int (*cmp)(const void*, const void*));

#endif