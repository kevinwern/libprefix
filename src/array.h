// array.h
// assigning string length based on characters
#ifndef ARRAY_H
#define ARRAY_H
#define DEFAULT_SIZE 2
#include "graph.h"

typedef struct DynArray {
  void **array;
  int  size;
  int  total;

} DynArray;

//Make array null
void nullDynArray(DynArray *a);

//Initialize array based on size
int initDynArray(DynArray *a, int size);

//Initialize array based on initial string
int initDynArrayStr(DynArray *a, char *str);

void initDynArrayHashed(DynArray *a);

//Remove last item in array, returning that item
char popDynArray(DynArray *a);

//Insert items into array
void insertDynArrayStr(DynArray *a, char *str);

//Insert single character into array
void insertDynArray(DynArray *a, char c);

//Insert node into array (for graph)
void insertDynArrayNode(DynArray *a, Node* n);

//Insert node into array hashed (for graph)
void insertDynArrayNodeHashed(DynArray *a, Node* n);

//Lookup char
Node *lookupDynArrayNodeHashed(DynArray *a, char key);

//Remove items based on size, items removed from end
void removeDynArray(DynArray *a, int remove);

//Free dynamic array structure
void clearDynArray(DynArray *a);

//Print contents of DynArray
void printDynArray(DynArray *a);

//Convert DynArray to string
char *DynArrayToStr(DynArray *a);

//Print contents of DynArray of nodes
char *DynArrayToStrNode(DynArray *a);

#endif
