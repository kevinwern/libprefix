// Graph.c
// Set implemented string comparison
#include <stdlib.h>
#include <stdio.h>
#include "array.h"
#include "graph.h"

void init_graph (Node* n){
  int i;
  DynArray *array = malloc(sizeof(DynArray));
  initDynArrayHashed(array);
  n->next = array;
}

/*void reinit_graph (Node* n){
  int i;
  for (i = 0; i < NEXT_ARR_SIZE; i++) {
    if (n->next[i] != NULL) {
	init_graph (n->next[i]);
	free (n->next[i]);
    }
  }
  n->next[i] = NULL;
}*/

int is_leaf (Node * n){
   return ((DynArray *)n->next)->total == 0;
}

// Look up a given word in the set
// Params: a node, a word
int find_word (Node *graph, char *word){
  Node *searchPointer = graph;
  while (*word != '\0' && searchPointer != NULL){
      searchPointer = lookupDynArrayNodeHashed((DynArray *)(searchPointer->next), *word);
      word++;
  }
  if (*word != '\0' || searchPointer == NULL)
    return 0;
  else
    return searchPointer->isword;
}

// Insert a new word into the set
// Params: a node, a word
int insert_word (Node *graph, char *word)
{
  Node *searchPointer = graph, *newest;
  while (*word != '\0'){
    newest = (Node *) malloc(sizeof (Node));
    init_graph (newest);
    newest->isword = 0;
    newest->key = *word;
    insertDynArrayNodeHashed((DynArray *)(searchPointer->next), newest);
    searchPointer = lookupDynArrayNodeHashed((DynArray *)(searchPointer->next), *word);
    word++;
  }
  searchPointer->isword = 1;
  return 0;
}

/** // Remove a word in the set
int delete_word (Node * graph, char *word){
  Node *lastword;
  while (*word != '\0' && graph != NULL){
    if (graph->isword)
      lastword = graph;
    graph = graph->next[character_hash (*word)];
    word++;
  }
  if (graph == NULL)
    return 1;
  graph->isword = 0;
  if (is_leaf (graph)){
    while (lastword != NULL){
      Node *temp = graph;
    }
  }
}

void print_graph (Node * graph){
  DynArray word;
  Node *path = graph;
  Node *pivot =NULL;
  Node *previous=NULL;
  initDynArray(&word,0);
  char i = 'a';

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
