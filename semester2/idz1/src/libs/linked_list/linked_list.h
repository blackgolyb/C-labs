#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct ListNode
{
    void *data;
    struct ListNode *next;
    struct ListNode *prev;
};

typedef struct List
{
    int type_size;
    struct ListNode *head;
} List;

List *ll_create(int type_size);
int ll_len(List *list);
void ll_destroy(List *list);
void ll_clear(List *list);
void ll_push_back(List *list, void *elem);
void *ll_get(List *list, int index);
void *ll_pop(List *list, int index);
void ll_insert(List *list, int index, void *elem);
void ll_set(List *list, int index, void *value);
List *ll_copy(List *list);

#endif