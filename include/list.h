#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct List;
typedef struct List List;

struct Node;
typedef struct Node Node;
typedef int data_t; // genesis of evil

Node* node_construct(data_t data, Node* next, Node* prev);

Node* node_next(Node* const node);
Node* node_next_n(Node* node, size_t n);
const Node* node_const_next(const Node* const node);
const Node* node_const_next_n(const Node* node, size_t n);
Node* node_prev(Node* const node);
Node* node_prev_n(Node* node, size_t n);
const Node* node_const_prev(const Node* const node);
const Node* node_const_prev_n(const Node* node, size_t n);
data_t node_data(const Node* const node);

size_t list_size(const List* const list);
Node* list_head(List* const list);
Node* list_tail(List* const list);
const Node* list_const_head(const List* const list);
const Node* list_const_tail(const List* const list);

List* list_construct(void);
List* list_copy(const List* const list);
void list_destruct(List* const list);

Node* list_push_front(List* const list, data_t data);
Node* list_push_back(List* const list, data_t data);
Node* list_insert_after(List* const list, Node* const node, data_t data);
void list_erase(List* const list, Node* const node);
void list_pop_back(List* const list);
void list_pop_front(List* const list);

void list_dump(const List* const list);

#endif