// hashtable.c -- Wraparound for DynArray
// that acts as a hash table.
#include "hashtable.h"

void init_hash_table(HashTable *h)
{
  init_dyn_array(h->array, DEFAULT_SIZE, UNCONTINUOUS);
}


