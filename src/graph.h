// Graph.h
// Set implemented string comparison

#ifndef GRAPH_H
#define GRAPH_H
#include <stdlib.h>
#include <wchar.h>

typedef struct Node {
  wchar_t key;
  int isword;
  void *next;
} Node;


Node *alloc_node();
void dealloc_node(Node *n);

void init_node(Node *n);
void clear_node(Node *n);

// Look up a given word in the set
// Params: a node, a word
int find_word(Node *graph, wchar_t *word);

// Insert a new word into the set
// Params: a node, a word
int insert_word(Node *graph, wchar_t *word);

// Remove a word in the set
int delete_word(Node *graph, wchar_t *word);

// Print the contents of a set
void print_graph(Node *graph);

static int is_leaf(Node *n);

#endif
