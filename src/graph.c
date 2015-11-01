// Graph.c
// Set implemented string comparison
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "array.h"
#include "hashtable.h"

void init_graph (Node *n){
  int i;
  HashTable *hashtable = malloc(sizeof(HashTable));
  init_hash_table(hashtable, DEFAULT_SIZE);
  n->next = hashtable;
}

static int is_leaf (Node *n){
   return ((HashTable *)n->next)->array->total == 0;
}

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
int delete_word (Node *graph, wchar_t *word)
{
  wchar_t *lastwordchar;
  Node *lastwordnode, *searchPointer = graph;
  while (*word != L'\0' && searchPointer != NULL){
    if (searchPointer->isword && ((HashTable *)(searchPointer->next))->array->total == 1){
      lastwordnode = searchPointer;
      lastwordchar = word;
    }
    searchPointer = lookup_node((HashTable *)(searchPointer->next), *word);
    word++;
  }
  if (searchPointer == NULL)
    return 1;
  searchPointer->isword = 0;
  if (is_leaf(searchPointer)){
    Node *next;
    while (next != NULL){
      next = lookup_node((HashTable *)(lastwordnode->next), *lastwordchar);
      delete_node((HashTable *)(lastwordnode->next), *lastwordchar);
      lastwordchar++;
    }
  }
  return 0;
}

/*void print_graph (Node * graph){
  DynArray word;
  Node *path = graph;
  Node *pivot =NULL;
  Node *previous=NULL;
  initDynArray(&word,0);
  wchar_t i = 'a';

  while(1) {
    if (i > 'z'){
       if (word.total == 0) break;
       else {
	 i = popDynArray(&word);
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
      insertDynArray(&word,i);
      previous = pivot;
      pivot = path;
      path = path->next[character_hash(i)];
      pivot->next[character_hash(i)] = previous;
      i = 'a';
      if (path->isword)
        printDynArray(&word);
    }
    else{
      i++;
    }
  }
}*/
