#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "array.h"
#include "graph.h"

typedef struct HashTable {
  DynArray *array;
} HashTable;

void init_hash_table(HashTable *h, int size);

void clear_hash_table(HashTable *h);

int insert_node(HashTable *h, char c);

Node* lookup_node(HashTable *h, char c);

static int find_hash_index(HashTable *h, char c);

static int find_initial_hash_index(HashTable *h, char c);

static void rekey_hash_table(HashTable *h);

#endif
