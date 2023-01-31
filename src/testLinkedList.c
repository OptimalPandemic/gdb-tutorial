#include <stdio.h>
#include <stdlib.h>
#include "testRunner.h"
#include "linkedList.h"


/*
 * UTILITY FUNCTIONS
*/

Node* initTest() {
    int test_data[] = {6, 3, 5, 10, 6, 39, 8};
    Node* key_list = (Node*) malloc(sizeof(Node));
    Node* temp = (Node*) malloc(sizeof(Node));
    Node* tempcurr = temp;
    temp->data = &test_data[0];
    key_list = temp;
    for (int i = 1; i < 7; i++) {
        Node *new = (Node*) malloc(sizeof(Node));
        new->data = &test_data[i];
        tempcurr->next = new;
        tempcurr = new;
    }

    // Clean up
    tempcurr = temp;
    Node* next;
    while (tempcurr != NULL) {
        next = tempcurr->next;
        free(tempcurr);
        tempcurr = next;
    }
    temp = NULL;
    
    return key_list;
}

Node* initList() {
    int test_data[] = {6, 3, 5, 10, 6, 39, 8};
    Node* list = create(&test_data[0], sizeof(int));
    for (int i = 1; i < 7; i++) {
        insert(list, &test_data[i], sizeof(int));
    }
    return list;
}

int int_cmp(const void* a, const void* b) {
    if (a == NULL || b == NULL) return 0;
    int x = *(int*)a;
    int y = *(int*)b;
    return x == y;
}

int compareLists(Node* l1, Node* l2) {
    Node *curr1 = l1;
    Node *curr2 = l2;
    while(curr1 != NULL && curr2 != NULL) {
        if (curr1->data != curr2->data)
            return 1;

        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    // Both lists should be empty by now if they're the same
    int result = (curr1 == NULL && curr2 == NULL);
    destroy(&curr1);
    destroy(&curr2);
    return result;
}

/*
 * TEST FUNCTIONS
*/

int testListCreate() {
    int t = 6;
    Node *test = create(&t, sizeof(int));
    int result = (*(int*)test->data == 6 && test->next == NULL);
    destroy(&test);
    return result;
}

int testListInsert() {
    Node *key = initTest();
    Node* test = initList();
    int result = compareLists(test, key);
    destroy(&test);
    return result;
}

int testListSearchPresent() {
    Node* test = initList();
    int t = 6;
    int result = *((int*)(search(test, &t, int_cmp))->data) == t;
    destroy(&test);
    return result;
}

int testListSearchNotPresent() {
    Node* test = initList();
    int t = 42;
    Node* res = (search(test, &t, int_cmp));
    int result = res == NULL;
    destroy(&test);
    return result;
}

int testListDestroy() {
    Node* test = initList();
    destroy(&test);
    int result = test == NULL;
    destroy(&test);
    return result;
}

int testListDeleteSingle() {
    int test_data[] = {6, 3, 5, 10, 6, 39, 8};
    Node* test = initList();
    Node* key = create(&test_data[0], sizeof(int));
    int data[] = {6, 5, 10, 6, 39, 8};
    for (int i = 1; i < 6; i++) {
        insert(test, &data[i], sizeof(data[i]));
    }
    delete(test, &test_data[1], int_cmp);
    int result = compareLists(test, key);
    destroy(&test);
    destroy(&key);
    return result;
}

int testListDeleteMultiple() {
    int test_data[] = {6, 3, 5, 10, 6, 39, 8};
    Node* test = initList();
    Node* key = create(&test_data[0], sizeof(int));
    int data[] = {3, 5, 10, 39, 8};
    for (int i = 1; i < 5; i++) {
        insert(test, &data[i], sizeof(data[i]));
    }
    delete(test, &test_data[0], int_cmp);
    int result = compareLists(test, key);
    destroy(&test);
    destroy(&key);
    return result;
}

int testInsertListNull () {
    Node* test = NULL;
    int t = 6;
    insert(test, &t, sizeof(int));
    return 1;
}

int testDeleteListNull() {
    Node* test = NULL;
    int t = 6;
    delete(test, &t, int_cmp);
    return 1;
}

int testDestroyListNull() {
    Node* test = NULL;
    destroy(&test);
    return 1;
}

int testSearchListNull() {
    Node* test = NULL;
    int t = 6;
    return search(test, &t, int_cmp) == NULL;
}

int testCreateDataNull() {
    int *t = NULL;
    return create(t, sizeof(int)) == NULL;
}

int testInsertDataNull() {
    int test_data[] = {6, 3, 5, 10, 6, 39, 8};
    Node* test = create(&test_data[0], sizeof(int));
    Node* key = create(&test_data[0], sizeof(int));
    for (int i = 1; i < 7; i++) {
        insert(test, &test_data[i], sizeof(test_data[i]));
        insert(key, &test_data[i], sizeof(test_data[i]));
    }
    int *t = NULL;
    insert(test, t, sizeof(int));
    int result = compareLists(test, key);
    destroy(&test);
    destroy(&key);
    return result;
}

int testDeleteDataNull() {
    int test_data[] = {6, 3, 5, 10, 6, 39, 8};
    Node* test = create(&test_data[0], sizeof(int));
    Node* key = create(&test_data[0], sizeof(int));
    for (int i = 1; i < 7; i++) {
        insert(test, &test_data[i], sizeof(test_data[i]));
        insert(key, &test_data[i], sizeof(test_data[i]));
    }
    int *t = NULL;
    delete(test, t, int_cmp);
    int result = compareLists(test, key);
    destroy(&test);
    destroy(&key);
    return result;
}

int testSearchDataNull() {
    int *t = NULL;
    int k = 6;
    Node* test = create(&k, sizeof(int));
    int result = search(test, t, int_cmp) == NULL;
    destroy(&test);
    return result;
}

int testSearchCmpNull() {
    int t = 6;
    Node* test = create(&t, sizeof(int));
    int (*cmp)(const void*, const void*) = NULL;
    int result = search(test, &t, cmp) == NULL;
    destroy(&test);
    return result;
}

int testCreateSizeZero() {
    int k = 6;
    Node* test = create(&k, 0);
    return test == NULL;
}

int testInsertSizeZero() {
    int test_data[] = {6, 3, 5, 10, 6, 39, 8};
    Node* test = create(&test_data[0], sizeof(int));
    Node* key = create(&test_data[0], sizeof(int));
    for (int i = 1; i < 7; i++) {
        insert(test, &test_data[i], sizeof(test_data[i]));
        insert(key, &test_data[i], sizeof(test_data[i]));
    }
    insert(test, &test_data[0], 0);
    int result = compareLists(test, key);
    destroy(&test);
    destroy(&key);
    return result;
}

void printTestList() {
    int test_data[] = {6, 3, 5, 10, 6, 39, 8};
    Node* test = create(&test_data[0], sizeof(int));
    for (int i = 1; i < 7; i++) {
        insert(test, &test_data[i], sizeof(test_data[i]));
    }
    Node* curr = test;

    while(curr != NULL) {
        printf("%i\n", *(int*)curr->data);
        curr = curr->next;
    }
    destroy(&test);
}

int main() {
    printf("\n**************** Linked Lists Tests ******************\n\n");
    int passed = 0;
    int failed = 0;
    int *p = &passed;
    int *f = &failed;
    runTest(testListCreate, "Create List Test", p, f);
    runTest(testListInsert, "Insert Into List Test", p, f);
    runTest(testListSearchPresent, "Search List (Item Present) Test", p, f);
    runTest(testListSearchNotPresent, "Search List (Item Not Present) Test", p, f);
    runTest(testListDestroy, "Destroy List Test", p, f);
    runTest(testListDeleteSingle, "Delete From List (Single Match) Test", p, f);
    runTest(testListDeleteMultiple, "Delete From List (Multiple Matches) Test", p, f);
    runTest(testInsertListNull, "Insert NULL List Test", p, f);
    runTest(testDeleteListNull, "Delete NULL List Test", p, f);
    runTest(testDestroyListNull, "Destroy NULL List Test", p, f);
    runTest(testSearchListNull, "Search NULL List Test", p, f);
    runTest(testCreateDataNull, "Create NULL Data Test", p, f);
    runTest(testInsertDataNull, "Insert NULL Data Test", p, f);
    runTest(testDeleteDataNull, "Delete NULL Data Test", p, f);
    runTest(testSearchDataNull, "Search NULL Data Test", p, f);
    runTest(testSearchCmpNull, "Search NULL Comparison Test", p, f);
    runTest(testCreateSizeZero, "Create Zero Size Test", p, f);
    runTest(testInsertSizeZero, "Insert Zero Size Test", p, f);
    printf("\ntestLinkedLists: %d tests passed. %d tests failed.\n\n", *p, *f);
    return 0;
}