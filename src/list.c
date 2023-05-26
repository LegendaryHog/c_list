#include <list.h>

struct Node
{
    Node* next;
    Node* prev;
    data_t data;
};

Node* node_construct(data_t data, Node* next, Node* prev)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL)
        return NULL;
    node->data = data;
    node->next = next;
    node->prev = prev;
    return node;
}

Node* node_next(Node* const node) {return node->next;}
const Node* node_const_next(const Node* const node) {return node->next;}
Node* node_prev(Node* const node) {return node->prev;}
const Node* node_const_prev(const Node* const node) {return node->prev;}

Node* node_next_n(Node* node, size_t n)
{
    for (size_t i = 0; i < n; i++, node = node->next) {;}
    return node;
}
Node* node_prev_n(Node* node, size_t n)
{
    for (size_t i = 0; i < n; i++, node = node->prev) {;}
    return node;
}
const Node* node_const_next_n(const Node* node, size_t n)
{
    for (size_t i = 0; i < n; i++, node = node->next) {;}
    return node;
}
const Node* node_const_prev_n(const Node* node, size_t n)
{
    for (size_t i = 0; i < n; i++, node = node->prev) {;}
    return node;
}
data_t node_data(const Node* const node) {return node->data;}

struct List
{
    size_t size;
    Node* head;
    Node* tail;
};

size_t list_size(const List* const list) {return list->size;}
Node* list_head(List* const list) {return list->head;}
const Node* list_const_head(const List* const list) {return list->head;}
Node* list_tail(List* const list) {return list->tail;}
const Node* list_const_tail(const List* const list) {return list->tail;}


List* list_construct(void)
{
    List* list = (List*)malloc(sizeof(List));
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

List* list_copy(const List* const list)
{
    assert(list);

    List* new_list = list_construct();
    if (new_list == NULL)
        return NULL;

    for (Node* node = list->head; node != NULL; node = node->next)
        list_push_back(new_list, node->data);

    return new_list;
}

void list_destruct(List* const list)
{
    Node* node = list->head;
    while (list->head != NULL)
        list_erase(list, list->head);
    free(list);
}

Node* list_push_front(List* const list, data_t data)
{
    assert(list);

    Node* new_node = node_construct(data, list->head, NULL);
    if (new_node == NULL)
        return NULL;

    if (list->head != NULL)
        list->head->prev = new_node;
    list->head = new_node;
    if (list->size == 0)
        list->tail = new_node;
    list->size++;

    return new_node;
}

Node* list_push_back(List* const list, data_t data)
{
    assert(list);

    if (list->size == 0)
        return list_push_front(list, data);

    list->tail->next = node_construct(data, NULL, list->tail);
    if (list->tail->next == NULL)
        return NULL;

    list->tail = list->tail->next;
    list->size++;

    return list->tail;
}

Node* list_insert_after(List* const list, Node* const node, data_t data)
{
    assert(list);

    if (node == NULL)
        return list_push_front(list, data);
    if (node == list->tail)
        return list_push_back(list, data);

    Node* new_node = node_construct(data, node->next, node);
    if (new_node == NULL)
        return NULL;
    node->next = new_node;
    new_node->next->prev = new_node;
    list->size++;

    return new_node;
}

void list_erase(List* const list, Node* const node)
{
    assert(list);
    assert(node);
    if (list->size == 0)
        return;

    if (node == list->head)
        list->head = list->head->next;
    if (node == list->tail)
        list->tail = list->tail->prev;

    if (node->prev != NULL)
        node->prev->next = node->next;
    if (node->next != NULL)
        node->next->prev = node->prev;

    list->size--;
    free(node);    
}

void list_pop_back(List* const list)
{
    list_erase(list, list->tail);
}

void list_pop_front(List* const list)
{
    list_erase(list, list->head);
}

void list_dump(const List* const list)
{
    fprintf(stderr, "LIST DUMP (%p):\n", list);
    fprintf(stderr, "\tsize = %zu\n", list->size);
    fprintf(stderr, "\thead = %p\n", list->head);
    fprintf(stderr, "\ttail = %p\n", list->tail);
    fprintf(stderr, "LIST:\n");
    for (Node* node = list->head; node != NULL; node = node->next)
        fprintf(stderr, "\t\tnode = %p [next = %p, prev = %p]\n", node, node->next, node->prev);
    fprintf(stderr, "DUMP END");
}