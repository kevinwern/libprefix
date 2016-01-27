// Graph.h
// Set implemented string comparison

#ifndef GRAPH_H
#define GRAPH_H
#include <stdlib.h>
#include <wchar.h>

typedef struct node {
  wchar_t key;
  int isword;
  void *next;
} node;


node *alloc_node();
void dealloc_node(node *n);

void init_node(node *n);
void clear_node(node *n);

// Look up a given word in the set
// Params: a node, a word
int find_word(node *graph, wchar_t *word);

// Insert a new word into the set
// Params: a node, a word
int insert_word(node *graph, wchar_t *word);

// Remove a word in the set
int delete_word(node *graph, wchar_t *word);

// Print the contents of a set
void print_graph(node *graph);

static int is_leaf(node *n);

#endif
