// Graph.c
// Set implemented string comparison
#include <stdlib.h>
#include "graph.h"

// Look up a given word in the set
// Params: a node, a word
int find_word (Node *graph, wchar_t *word){
  Node *searchPointer = graph;
  while (*word != L'\0' && searchPointer != NULL){
      searchPointer = lookup_node((HashTable *)(searchPointer->next), *word);
     word++;
  }
  if (*word != L'\0' || searchPointer == NULL)
    return 0;
  else
    return searchPointer->isword;
}

static Node *find_word_node(Node *graph, wchar_t *word){
  Node *searchPointer = graph;
  while (*word != L'\0' && searchPointer != NULL){
      searchPointer = lookup_node((HashTable *)(searchPointer->next), *word);
     word++;
  }
  if (*word != L'\0' || searchPointer == NULL)
    return NULL;
  else
    return searchPointer;
}

// Insert a new word into the set
// Params: a node, a word
int insert_word (Node *graph, wchar_t *word)
{
  Node *searchPointer = graph;
  while (*word != L'\0'){
    insert_node((HashTable *)(searchPointer->next), *word);
    searchPointer = lookup_node((HashTable *)(searchPointer->next), *word);
    word++;
  }
  searchPointer->isword = 1;
  return 0;
}

// Remove a word in the set
// Params: a node, a word
int delete_word (Node *graph, wchar_t *word)
{
  Node *lastwordnode = NULL, *searchPointer = graph;
  while (*word != L'\0' && searchPointer != NULL){
    if (searchPointer->isword && ((HashTable *)(searchPointer->next))->array->total == 1){
      lastwordnode = searchPointer;
    }
    else if (((HashTable *)(searchPointer->next))->array->total > 1) {
      lastwordnode = NULL;
    }
    searchPointer = lookup_node((HashTable *)(searchPointer->next), *word);
    word++;
  }
  if (searchPointer == NULL)
    return 1;
  searchPointer->isword = 0;
  if (lastwordnode != NULL){
    clear_node(lastwordnode);
    dealloc_node(lastwordnode);
  }
  return 0;
}
