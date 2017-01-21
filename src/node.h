#ifndef NODE_H
#define NODE_H
#include <wchar.h>

typedef struct Node {
  wchar_t key;
  int isword;
  void *next;
  void *data;
} Node;

Node *alloc_node();
void dealloc_node(Node *n);
int is_leaf(Node *n);

void init_node(Node *n);
void clear_node(Node *n);

#endif
