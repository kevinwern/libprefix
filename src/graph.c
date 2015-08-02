// Graph.c
// Set implemented string comparison
#include <stdlib.h>
#include <stdio.h>
#include "array.h"
#include "graph.h"

void init_graph (Node* n){
  int i;
  for (i = 0; i < NEXT_ARR_SIZE; i++){
      n->next[i] = NULL;
  }
}

void reinit_graph (Node* n){
  int i;
  for (i = 0; i < NEXT_ARR_SIZE; i++) {
    if (n->next[i] != NULL) {
	init_graph (n->next[i]);
	free (n->next[i]);
    }
  }
  n->next[i] = NULL;
}

// Character hash
int character_hash (char c){
  return c % 26;
}

int is_leaf (Node * n){
  int i;
  for (i = 0; i < NEXT_ARR_SIZE; i++){
      if (n->next != NULL)
	return 0;
  }
  return 1;
}

// Look up a given word in the set
// Params: a node, a word
int find_word (Node * graph, char *word){
  while (*word != '\0' && graph != NULL){
      graph = graph->next[character_hash (*word)];
      word++;
  }
  if (*word != '\0' || graph == NULL)
    return 0;
  else
    return graph->isword;
}

// Insert a new word into the set
// Params: a node, a word
int insert_word (Node * graph, char *word)
{
  while (*word != '\0'){
      if (graph->next[character_hash (*word)] == NULL){
        Node *newest = malloc (sizeof (Node));
	init_graph (newest);
	newest->isword = 0;
	graph->next[character_hash (*word)] = newest;
      }
      graph = graph->next[character_hash (*word)];
      word++;
  }
  graph->isword = 1;
  return 0;
}

// Remove a word in the set
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
}
