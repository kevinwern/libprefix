// Graph.h
// Set implemented string comparison

#ifndef GRAPH_H
#define GRAPH_H
#include <stdlib.h>

typedef struct Node {
  char key;
  int  isword;
  void *next;
} Node;

void init_graph(Node *n);

// Look up a given word in the set
// Params: a node, a word
int find_word(Node *graph, char *word);

// Insert a new word into the set
// Params: a node, a word
int insert_word(Node *graph, char *word);

// Remove a word in the set
int delete_word(Node *graph, char *word);

// Print the contents of a set
void print_graph(Node *graph);

static int is_leaf(Node *n);

#endif
