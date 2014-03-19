// Graph.h
// Set implemented string comparison

#ifndef GRAPH_H
#define GRAPH_H

typedef struct {
  char      key;
  int       isword;
  Node*     next[26];
} Node;


int character_hash(char c){
  return c % 26;
}

int is_leaf(Node *n){
   int i;
   for (i = 0; i < 26; i++) {
     if (n->next != NULL) return 0;
   }
   return 1;
}

// Look up a given word in the set
// Params: a node, a word
int find_word(Node *graph, char *word){
  
   while (word != NULL && graph != NULL){
      graph = graph->next[character_hash(word)];
      word++;
   }

   if (word != NULL || graph == NULL) return 0;
   else return graph->isword;
}

// Insert a new word into the set
// Params: a node, a word
int insert_word(Node *graph, char *word){
  
  while (word != NULL) {

    if (graph->next == NULL){
      Node *newest = malloc(sizeof(Node));
      newest->isword = false;
      graph->next[character_hash(word)] = newest;
    }

    graph = graph->next;
    word++;
  }

  graph->isword = true;
  return 0;
}

// Remove a word in the set
int delete_word(Node *graph, char *word){

  Node *lastword;
  while (word != NULL && graph != NULL) {

    if (graph->isword) lastword = graph;

    graph = graph->next;
    word++;
  }

  if (graph == NULL) return 1;

  graoh->isword = 0;
  if (is_leaf(graph)){

    while (lastword != NULL)
    Node* temp = graph
  }
}

#endif
