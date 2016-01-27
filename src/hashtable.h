#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "array.h"
#include "graph.h"

typedef struct hash_table {
  dyn_array *array;
} hash_table;

void init_hash_table(hash_table *h, int size);

void clear_hash_table(hash_table *h);

hash_table *alloc_hash_table();

int insert_node(hash_table *h, wchar_t c);

node* lookup_node(hash_table *h, wchar_t c);

int delete_node(hash_table *h, wchar_t c);

static void resize_and_rekey_hash_table(hash_table *h, int size);

static void rekey_hash_table(hash_table *h, dyn_array *a);

static int find_hash_index(hash_table *h, wchar_t c);

static int find_initial_hash_index(hash_table *h, wchar_t c);

#endif
