#include "node.h"
#include "hashtable.h"
#include "liberrors.h"

Node *alloc_node()
{
  Node *node = malloc(sizeof(Node));
  LIBPREFIX_ASSERT(node != NULL, MALLOC_FAILED, NULL);
  node->next = NULL;
  node->isword = 0;
  return node;
}

void dealloc_node(Node *n)
{
  free(n);
}

void init_node (Node *n)
{
  HashTable *hashtable = alloc_hash_table();
  init_hash_table(hashtable, DEFAULT_SIZE);
  n->next = hashtable;
}

void clear_node (Node *n){
  if (n->next != NULL)
  {
    clear_hash_table(n->next);
    dealloc_hash_table(n->next);
    n->next = NULL;
  }
  free(n->next);
}

int is_leaf (Node *n){
   HashTable *hash_table = n->next;
   return hash_table->array->total == 0;
}

