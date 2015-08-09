// libprefix array.c
// Implemented functions for array.h
//
#include "array.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Initialize all array values to empty
void nullDynArray(DynArray *a){
  a->size = DEFAULT_SIZE;
  a->total = 0;
  a->array = malloc(sizeof(void *) * DEFAULT_SIZE);
  a->array[1] = NULL;
  a->array[2] = NULL;
}

//Initialize array based on size
int initDynArray(DynArray *a, int size){
  a->size = DEFAULT_SIZE;
  while (a->size<size)
    a->size *= 2;
  a->array = malloc(sizeof(void *) * a->size);
  a->total = 0;
  return 0;
}

void initDynArrayHashed(DynArray *a){
  int i;
  a->size = DEFAULT_SIZE;
  a->array = (void **)malloc(sizeof(void *) * a->size);
  a->total = 0;
  for(i = 0; i < DEFAULT_SIZE; i++)
  {
    a->array[i] = NULL;
  }
}

//Initialize array based on initial string
int initDynArrayStr(DynArray *a, char *str){
  int size = strlen(str);
  int i;
  a->size = DEFAULT_SIZE;
  while (a->size<size)
    a->size *= 2;
  a->array = (void**) malloc(sizeof(void *) * a->size);
  for (i = 0; i<a->size; i++)
  {
    a->array[i] = (void *) malloc(sizeof(char));
  }
  a->total = size;

  for(i = 0; i<size; i++){
    *(char *)((char **)a->array)[i] = str[i];
  }
  return 0;
}

//Insert items into array
void insertDynArrayStr(DynArray *a, char *str){
  int addsize = strlen(str);
  int size = a->size;
  int i;
  if (a->array != NULL){
    while (a->size < a->total+addsize){
      a->size *= 2;
    }
    a->array = (void **) realloc(a->array, sizeof(void *) * a->size);

    for (i = size; i<a->size; i++)
    {
      a->array[i] = (void *) malloc(sizeof(char));
    }
    for (i = 0; i < addsize; i++){
      *(char *)((char **)a->array)[i+a->total] = str[i];
    }
    a->total = a->total+addsize;
  }
}

void insertDynArray(DynArray *a, char c){
  if (a->array != NULL){
    int size = a->size;
int i;
    while (a->size < a->total+1){
}
    a->array = (void**) realloc(a->array, sizeof(void *) * a->size);
    for (i=size; i<a->size; i++)
    {
      a->array[i] = (void *) malloc(sizeof(char));
    }
    *(char *)((char **)a->array)[a->total] = c;
    a->total=a->total+1;
  }
}

void insertDynArrayNode(DynArray *a, Node *n)
{
  if (a->array != NULL){
    int size = a->size;
    int i;
    while (a->size < a->total+1){
      a->size *= 2;
    }
    a->array = (void**) realloc(a->array, sizeof(void *) * a->size);
    for (i=size; i<a->size; i++)
    {
      a->array[i] = (void *) malloc(sizeof(Node *));
    }
    ((Node **)a->array)[a->total] = n;
    a->total=a->total+1; 
  }
}

void insertDynArrayNodeHashed(DynArray *a, Node *n)
{
  if (a->array != NULL){
    int size = a->size;
    int i;
    a->total += 1;
    if (a->size < a->total){
      while (a->size < a->total){
        a->size *= 2;
      }
      a->array = (void **) realloc(a->array, sizeof(void *) * a->size);
      for (i=size; i<a->size; i++)
      {
	a->array[i] = NULL;
      }
      for (i=0; i<size; i++)
      {
	Node *toReinsert;
        if (a->array[i] != NULL)
	{
	  a->total -= 1;
	  toReinsert = ((Node **)a->array)[i];
	  a->array[i] = NULL;
	  insertDynArrayNodeHashed(a, toReinsert);
	}
      }
    }
    else {
      if (a->array[n->key % a->size] == NULL){
        ((Node **)a->array)[n->key % a->size] = n;
      }
      else {
	int j = 0;
	while (a->array[(n->key + j) % a->size] != NULL && ((Node **)a->array)[(n->key + j) % a->size]->key == n->key){
	  j++;
	}
	if (((Node **)a->array)[(n->key+j) % a->size]->key != n->key)
	{
	  ((Node **)a->array)[n->key % a->size] = n;
	}
      }
    }
  }
}

Node *lookupDynArrayNodeHashed(DynArray *a, char c)
{
  if (a->array != NULL){
    int keyName = c;
    while (((Node **)a->array)[keyName % a->size] != NULL && ((Node **)a->array)[keyName % a->size]->key != c && keyName != c+a->size){
      keyName++;
    }
    if (((Node **)a->array)[keyName % a->size] != NULL && ((Node *)((Node **)a->array)[keyName % a->size])->key == c){
        return (Node*)((Node **)a->array)[keyName % a->size];
    }
    else
      return NULL;
  }
  return NULL;
}

//Remove items based on size, items removed from end
void removeDynArray(DynArray *a, int remove){
  int newsize = a->total-remove;
  if (a->array != NULL && newsize >= 0){
    while (a->size / 2 > newsize){
      a->size /= 2;
    }
    a->total = newsize;
    a->array = (void **) realloc(a->array, sizeof(void *) * a->size);
  }
}

//returns last character in array
char popDynArray(DynArray *a){
  if (a->total == 0) return 0;

  int newsize = a->total-1;
  if (a->array != NULL && newsize >=0){
    while (a->size / 2 > newsize){
      a->size /= 2;
    }
    char toReturn = *(char *)((char **)a->array)[a->total-1];
    a->total = newsize;
    a->array = realloc(a->array, sizeof(void *) * a->size);
    return toReturn;
  }
  else {
    return 0;
  }	  
}

//Print contents of a DynArray
void printDynArray(DynArray *a){
  int i;
  for (i = 0; i < a->total; i++){
    printf("%c", *(char *)a->array[i]);
  }
  printf("\n");
}

//Convert DynArray to a string
char *DynArrayToStr(DynArray *a){
  char* return_string = malloc(sizeof(char) * (a->total+1));
  int i;
  for (i = 0; i < a->total; i++){
    return_string[i] = *(char *) a->array[i];
  }
  return_string[i] = '\0';
  return return_string;
}

//Convert DynArray to a string
char *DynArrayToStrNode(DynArray *a){
  char* return_string = malloc(sizeof(char) * (a->total+1));
  int i;
  for (i = 0; i < a->total; i++){
    return_string[i] = ((Node *)((Node **) a->array)[i])->key;
  }
  return_string[i] = '\0';
  return return_string;
}

//Free dynamic array structure
void clearDynArray(DynArray *a){
  if (a->size != 0){
    free(a->array);
    a->total = 0;
    a->size = 0;
    a->array = NULL;
  }
}
