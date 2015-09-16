// hashtable.c -- Wraparound for DynArray
// that acts as a hash table.
#include "hashtable.h"

void init_hash_table(HashTable *h, int size)
{
  h->array = malloc(sizeof(DynArray));
  init_dyn_array(h->array, NON_CONTINUOUS, size);
}

void clear_hash_table(HashTable *h)
{
  clear_dyn_array(h->array);
  free(h->array);
}

Node *lookup_node(HashTable *h, char c)
{
  int index = find_hash_index(h,c);
  if (index < 0) {
    return NULL;
  }
  else {
    return lookup_dyn_array_node(h->array, index);
  }
}

int insert_node(HashTable *h, char c)
{
  if (lookup_node(h, c) != NULL) {
    return -1;
  }
  if (h->array->total == h->array->size)
  {
    rekey_hash_table(h);
  }
  Node *node = (Node *) malloc(sizeof(node));
  node->key = c;
  int index = find_hash_index(h, c);
  insert_dyn_array_node(h->array, node, index);
  return 0;
}

static void rekey_hash_table(HashTable *h)
{
  Node *current;
  int i;
  DynArray *new_array = malloc(sizeof(DynArray));
  DynArray *old_array = h->array;
  init_dyn_array(new_array, NON_CONTINUOUS, h->array->size*2);
  h->array = new_array;
  for (i = 0; i < old_array->size; i++)
  {
    current = lookup_dyn_array_node(old_array, i);
    insert_node(h, current->key);
  }
  free(old_array);
}

static int find_hash_index(HashTable *h, char c)
{
  int initial_index = find_initial_hash_index(h, c);
  int i;
  Node *result = NULL;
  for (i = 0; i < h->array->size; i++)
  {
    int index = (initial_index + i) % h->array->size;
    Node *result = lookup_dyn_array_node(h->array, index);
    if (result == NULL || result->key == c) {
      return index;
    }
  }
  return -1;
}

static int find_initial_hash_index(HashTable *h, char c)
{
  return c % h->array->size;
}
