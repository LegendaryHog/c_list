#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct List;
typedef struct List List;

struct Node;
typedef struct Node Node;

struct type_info;
typedef struct type_info type_info;

typedef void (*type_copy_func)(void* const, const void* const);
typedef void (*destructor_func)(void* const);

Node* node_construct(const void* const source, type_info* type, Node* next, Node* prev);
void  node_destruct(Node* const node);

Node* node_next(Node* const node);
Node* node_next_n(Node* node, size_t n);
const Node* node_const_next(const Node* const node);
const Node* node_const_next_n(const Node* node, size_t n);
Node* node_prev(Node* const node);
Node* node_prev_n(Node* node, size_t n);
const Node* node_const_prev(const Node* const node);
const Node* node_const_prev_n(const Node* node, size_t n);

void node_data_get(const Node* const node, void* const dest);
void node_data_set(Node* const node, const void* const source);

size_t list_size(const List* const list);
Node* list_head(List* const list);
Node* list_tail(List* const list);
const Node* list_const_head(const List* const list);
const Node* list_const_tail(const List* const list);

List* list_construct(size_t size_of_type, type_copy_func copy_func, destructor_func dtor_func);
List* list_copy(const List* const list);
void list_destruct(List* const list);

Node* list_push_front(List* const list, const void* const source);
Node* list_push_back(List* const list, const void* const source);
Node* list_insert_after(List* const list, Node* const node, const void* const source);
void list_erase(List* const list, Node* const node);
void list_pop_back(List* const list);
void list_pop_front(List* const list);

void list_dump(const List* const list);

#endif