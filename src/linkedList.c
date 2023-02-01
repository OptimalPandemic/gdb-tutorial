#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"


Node* create(void *data, size_t size) {
    if (data == NULL || size == 0)
        return NULL;

    Node *head = (Node*) malloc(sizeof(Node));    

    head->data = malloc(size);
    memcpy(head->data, data, size);
    head->next = NULL;

    return head;
}

void destroy(Node** list) {
    if (*list == NULL)
        return;

    Node *curr = *list;
    Node *next;

    while(curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    
    *list = NULL;
}

/**
 * Returns the final Node in a List.
 * 
 * @param List* list    The List to search.
 * @returns Node*
*/
Node* findTail(Node* list) {
    Node* curr = list;

    while(curr->next != NULL) {
        curr = curr->next;
    }

    return curr;
}

void insert(Node* list, void *data, size_t size) {
    if (list == NULL || data == NULL || size == 0)
        return;

    Node *new = (Node*) malloc(sizeof(Node));
    Node *curr = findTail(list);

    new->data = malloc(size);
    memcpy(new->data, data, size);

    new->next = NULL;
    curr->next = new;
}

void delete(Node* list, void* data, int (*cmp)(const void*, const void*)) {
    if (list == NULL || data == NULL || cmp == NULL)
        return;

    Node *curr = list;
    Node *prev = NULL;

    // Find the first occurrance
    while(curr && cmp(curr->data, data)) {
        curr = curr->next;
    }

    while(curr) {
        if(cmp(curr->data, data))
            prev->next = curr->next;
        else
            prev = curr;
        curr = curr->next;
    }
}

Node* search(Node* list, void* data, int (*cmp)(const void*, const void*)) {
    if (list == NULL || data == NULL || cmp == NULL)
        return NULL;

    Node *curr = list;

    while(curr->data != NULL) {
        if (cmp(curr->data, data))
            return curr;
        curr = curr->next;
    }

    return NULL;
}