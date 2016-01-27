// hashtable.c -- Wraparound for dyn_array
// that acts as a hash table.
#include "hashtable.h"

void init_hash_table(hash_table *h, int size)
{
  h->array = alloc_dyn_array();
  init_dyn_array(h->array, NON_CONTINUOUS, size);
}

void clear_hash_table(hash_table *h)
{
  if (h->array != NULL) {
    clear_dyn_array(h->array);
  }
  dealloc_dyn_array(h->array);
}

hash_table *alloc_hash_table()
{
  hash_table *hash_table = malloc(sizeof(hash_table));
  hash_table->array = NULL;
  return hash_table;
}

void dealloc_hash_table(hash_table *h)
{
  free(h);
}

node *lookup_node(hash_table *h, wchar_t c)
{
  int index = find_hash_index(h,c);
  if (index < 0) {
    return NULL;
  }
  else {
    return lookup_dyn_array_node(h->array, index);
  }
}

int insert_node(hash_table *h, wchar_t c)
{
  if (lookup_node(h, c) != NULL) {
    return -1;
  }
  if (h->array->total == h->array->size) {
    resize_and_rekey_hash_table(h, h->array->size * 2);
  }
  node *node = alloc_node();
  init_node(node);
  node->key = c;
  node->isword = 0;
  int index = find_hash_index(h, c);
  insert_dyn_array_node(h->array, node, index);
  return 0;
}

int delete_node(hash_table *h, wchar_t c)
{
  if (lookup_node(h, c) == NULL) {
    return -1;
  }
  if (h->array->total == h->array->size/2 && h->array->size != 2) {
    resize_and_rekey_hash_table(h, h->array->size / 2);
  }
  int index = find_hash_index(h, c);
  delete_dyn_array_node(h->array, index);
  return 0;
}

static void resize_and_rekey_hash_table(hash_table *h, int size)
{
  dyn_array *old_array = h->array;
  dyn_array *new_array = alloc_dyn_array();
  init_dyn_array(new_array, NON_CONTINUOUS, size);
  h->array = new_array;
  h->array->size = size;
  rekey_hash_table(h, old_array);
  dealloc_dyn_array(old_array);
}

static int reinsert_node(hash_table *h, node *n)
{
  if (lookup_node(h, n->key) != NULL) {
    return -1;
  }
  int index = find_hash_index(h, n->key);
  insert_dyn_array_node(h->array, n, index);
  return 0;
}

static void rekey_hash_table(hash_table *h, dyn_array *a)
{
  node *current;
  int i;
  for (i = 0; i < a->size; i++)
  {
    current = lookup_dyn_array_node(a, i);
    if (current != NULL) {
      reinsert_node(h, current);
    }
  }
}

static int find_hash_index(hash_table *h, wchar_t c)
{
  int initial_index = find_initial_hash_index(h, c);
  int i;
  node *result = NULL;
  for (i = 0; i < h->array->size; i++)
  {
    int index = (initial_index + i) % h->array->size;
    node *result = lookup_dyn_array_node(h->array, index);
    if (result == NULL || result->key == c) {
      return index;
    }
  }
  return -1;
}

static int find_initial_hash_index(hash_table *h, wchar_t c)
{
  return c % h->array->size;
}
