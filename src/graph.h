// Graph.h
// Set implemented string comparison

#ifndef GRAPH_H
#define GRAPH_H
#include <stdlib.h>
#define NEXT_ARR_SIZE 26

typedef struct Node {
  char         key;
  int          isword;
  struct Node  *next[NEXT_ARR_SIZE];
} Node;

void init_graph(Node *n);
int character_hash(char c);
int is_leaf(Node *n);

// Look up a given word in the set
// Params: a node, a word
int find_word(Node *graph, char *word);

// Insert a new word into the set
// Params: a node, a word
int insert_word(Node *graph, char *word);

// Remove a word in the set
int delete_word(Node *graph, char *word);
#endif
