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

Node *lookup_node(HashTable *h, wchar_t c)
{
  int index = find_hash_index(h,c);
  if (index < 0) {
    return NULL;
  }
  else {
    return lookup_dyn_array_node(h->array, index);
  }
}

int insert_node(HashTable *h, wchar_t c)
{
  if (lookup_node(h, c) != NULL) {
    return -1;
  }
  if (h->array->total == h->array->size)
  {
    resize_and_rekey_hash_table(h, h->array->size * 2);
  }
  Node *node = (Node *) malloc(sizeof(Node));
  node->key = c;
  node->next = (HashTable *) malloc(sizeof(HashTable));
  init_hash_table((HashTable *) node->next, DEFAULT_SIZE);
  node->isword = 0;
  int index = find_hash_index(h, c);
  insert_dyn_array_node(h->array, node, index);
  return 0;
}

int delete_node(HashTable *h, wchar_t c)
{
  if (lookup_node(h, c) == NULL) {
    return -1;
  }
  if (h->array->total == h->array->size/2 && h->array->size != 2)
  {
    resize_and_rekey_hash_table(h, h->array->size / 2);
  }
  int index = find_hash_index(h, c);
  delete_dyn_array_node(h->array, index);
  return 0;
}

static void resize_and_rekey_hash_table(HashTable *h, int size)
{
  DynArray *old_array = h->array;
  DynArray *new_array = malloc(sizeof(DynArray));
  h->array = new_array;
  h->array->size = size;
  init_dyn_array(new_array, NON_CONTINUOUS, size);
  rekey_hash_table(h, old_array);
  free(old_array);
}

static void rekey_hash_table(HashTable *h, DynArray *a)
{
  Node *current;
  int i;
  for (i = 0; i < a->size; i++)
  {
    current = lookup_dyn_array_node(a, i);
    if (current != NULL) {
      insert_node(h, current->key);
    }
  }
}

static int find_hash_index(HashTable *h, wchar_t c)
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

static int find_initial_hash_index(HashTable *h, wchar_t c)
{
  return c % h->array->size;
}
