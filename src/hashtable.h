#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "array.h"

typedef struct HashTable {
  DynArray array;
}

void init_hash_table(HashTable *h);

#endif
