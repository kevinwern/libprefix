#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "array.h"
#include "graph.h"

typedef struct HashTable {
  DynArray *array;
} HashTable;

HashTable *alloc_hash_table();

void dealloc_hash_table();

void init_hash_table(HashTable *h, int size);

void clear_hash_table(HashTable *h);

int insert_node(HashTable *h, wchar_t c);

Node* lookup_node(HashTable *h, wchar_t c);

int delete_node(HashTable *h, wchar_t c);

static void resize_and_rekey_hash_table(HashTable *h, int size);

static void rekey_hash_table(HashTable *h, DynArray *a);

static int find_hash_index(HashTable *h, wchar_t c);

static int find_initial_hash_index(HashTable *h, wchar_t c);

#endif
