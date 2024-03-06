#include "linked_list.h"

List *ll_create(int type_size)
{
    List *list = malloc(sizeof(List));
    list->type_size = type_size;
    list->head = NULL;
    return list;
}

int ll_len(List *list)
{
    int len = 0;
    for (struct ListNode *node = list->head; node; node = node->next)
        len++;

    return len;
}

void ll_destroy(List *list)
{
    for (struct ListNode *node = list->head; node; node = node->next)
    {
        free(node->data);
        // node->data = NULL;
        // free(node);
    }
    // free(list);
}

void ll_clear(List *list)
{
    for (struct ListNode *node = list->head; node; node = node->next)
    {
        free(node->data);
        node->data = NULL;
    }
    list->head = NULL;
}

void ll_push_back(List *list, void *elem)
{
    struct ListNode *last_node = list->head;

    if (!last_node)
    {
        list->head = malloc(sizeof(struct ListNode));
        list->head->data = elem;
        list->head->next = NULL;
        list->head->prev = NULL;
        return;
    }

    while (last_node->next)
        last_node = last_node->next;

    last_node->next = malloc(sizeof(struct ListNode));
    last_node->next->data = elem;
    last_node->next->next = NULL;
    last_node->next->prev = last_node;
}

void *ll_get(List *list, int index)
{
    int i = 0;
    struct ListNode *node = list->head;

    for (; node && (i != index); node = node->next)
        i++;

    if (!node)
        return NULL;

    return node->data;
}

void *ll_pop(List *list, int index)
{
    int i = 0;
    struct ListNode *node = list->head;

    for (; node && (i != index); node = node->next)
        i++;

    if (!node)
        return NULL;

    void *data = node->data;

    if (node->next)
        node->next->prev = node->prev;

    if (node->prev)
        node->prev->next = node->next;

    if (node == list->head)
        list->head = node->next;

    free(node);

    return data;
}

void ll_insert(List *list, int index, void *elem)
{
    struct ListNode *node = list->head;
    if (index == 0)
    {
        struct ListNode *new_node = malloc(sizeof(struct ListNode));
        new_node->data = elem;
        new_node->next = node;
        new_node->prev = NULL;
        list->head = new_node;
        node->prev = new_node;
        return;
    }

    int n = ll_len(list);
    if (index == n)
    {
        ll_push_back(list, elem);
        return;
    }

    if (index > n || index < 0)
        return;

    for (int i = 0; node && (i != index); i++)
        node = node->next;

    if (!node)
        return;

    struct ListNode *new_node = malloc(sizeof(struct ListNode));
    new_node->data = elem;
    new_node->next = node;
    new_node->prev = node->prev;
    node->prev->next = new_node;
    node->prev = new_node;
}

void ll_set(List *list, int index, void *value)
{
    struct ListNode *node = list->head;
    for (int i = 0; node && (i != index); node = node->next)
        i++;

    if (!node)
        return;

    node->data = value;
}

List *ll_copy(List *list)
{
    List *new_list = ll_create(list->type_size);
    void *tmp;
    for (struct ListNode *node = list->head; node; node = node->next)
    {
        tmp = malloc(list->type_size);
        memcpy(tmp, node->data, list->type_size);
        ll_push_back(new_list, tmp);
    }

    return new_list;
}