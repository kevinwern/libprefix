// Graph.h
// Set implemented string comparison

#ifndef GRAPH_H
#define GRAPH_H
#include <stdlib.h>
#include <wchar.h>
#include "node.h"
#include "array.h"
#include "hashtable.h"

typedef struct PrefixResult {
  wchar_t *word;
  struct PrefixResult *next;
} PrefixResult;

// Look up a given word in the set
// Params: a node, a word
int find_word(Node *graph, wchar_t *word);

// Insert a new word into the set
// Params: a node, a word
int insert_word(Node *graph, wchar_t *word);

// Remove a word in the set
int delete_word(Node *graph, wchar_t *word);

// Print the contents of a set
PrefixResult *search_prefix(Node *graph, wchar_t *search_string);

static int get_permutations(Node *graph, DynArray *current_string, PrefixResult **collection);

#endif
