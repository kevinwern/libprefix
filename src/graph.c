// Graph.c
// Core functionality for inserting, looking up, and deleting words.
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "array.h"
#include "hashtable.h"

node *alloc_node()
{
  node *node = malloc(sizeof(node));
  node->next = NULL;
  node->isword = 0;
  return node;
}

void dealloc_node(node *n)
{
  free(n);
}

void init_node (node *n){
  int i;
  hash_table *hashtable = alloc_hash_table();
  init_hash_table(hashtable, DEFAULT_SIZE);
  n->next = hashtable;
}

void clear_node (node *n){
  if (n->next != NULL)
  {
    clear_hash_table(n->next);
    dealloc_hash_table(n->next);
    n->next = NULL;
  }
  free(n->next);
}

static int is_leaf (node *n){
   return ((hash_table *)n->next)->array->total == 0;
}

// Look up a given word in the set
// Params: a node, a word
int find_word (node *graph, wchar_t *word){
  node *searchPointer = graph;
  while (*word != L'\0' && searchPointer != NULL){
      searchPointer = lookup_node((hash_table *)(searchPointer->next), *word);
     word++;
  }
  if (*word != L'\0' || searchPointer == NULL)
    return 0;
  else
    return searchPointer->isword;
}

// Insert a new word into the set
// Params: a node, a word
int insert_word (node *graph, wchar_t *word)
{
  node *searchPointer = graph;
  while (*word != L'\0'){
    insert_node((hash_table *)(searchPointer->next), *word);
    searchPointer = lookup_node((hash_table *)(searchPointer->next), *word);
    word++;
  }
  searchPointer->isword = 1;
  return 0;
}

// Remove a word in the set
int delete_word (node *graph, wchar_t *word)
{
  node *lastwordnode = NULL, *searchPointer = graph;
  while (*word != L'\0' && searchPointer != NULL){
    if (searchPointer->isword && ((hash_table *)(searchPointer->next))->array->total == 1){
      lastwordnode = searchPointer;
    }
    else if (((hash_table *)(searchPointer->next))->array->total > 1) {
      lastwordnode = NULL;
    }
    searchPointer = lookup_node((hash_table *)(searchPointer->next), *word);
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

/**
void print_graph (node * graph){
  dyn_array word;
  node *path = graph;
  node *pivot =NULL;
  node *previous=NULL;
  init_dyn_array(&word,0);
  wchar_t i = 'a';

  while(1) {
    if (i > 'z'){
       if (word.total == 0) break;
       else {
	 i = popdyn_array(&word);
	 pivot->next[character_hash(i)] = path;
	 path = pivot;
	 pivot = previous;
	 if (word.total != 0)
	   previous = previous->next[character_hash(word.array[word.total-1])];
	 i++;
	 continue;
       }
    }

    if (path->next[character_hash(i)] != NULL){
      insertdyn_array(&word,i);
      previous = pivot;
      pivot = path;
      path = path->next[character_hash(i)];
      pivot->next[character_hash(i)] = previous;
      i = 'a';
      if (path->isword)
        printdyn_array(&word);
    }
    else{
      i++;
    }
  }
}*/
