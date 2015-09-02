// libprefix array.c
// Implemented functions for array.h
 
#include "array.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Initialize array, optionally based on size;
int init_dyn_array(DynArray *a, int size = DEFAULT_SIZE){
  int i;
  a->size = DEFAULT_SIZE;
  while (a->size<size)
    a->size *= 2;
  a->total = 0;
  a->array = malloc(sizeof(void *) * a->size);
  for (i = 0; i < DEFAULT_SIZE; i++){
    a->array[i] = NULL;
  }
  return 0;
}

void init_dyn_array_hashed(DynArray *a, int size = DEFAULT_SIZE){
  int i;
  a->size = DEFAULT_SIZE;
  while (a->size<size)
    a->size *= 2;
  a->array = (void **)malloc(sizeof(void *) * a->size);
  a->total = 0;
  for(i = 0; i < DEFAULT_SIZE; i++)
  {
    a->array[i] = NULL;
  }
}

void insert_dyn_array_char(DynArray *a, char c){
  if (a->array != NULL){
    int size = a->size;
    int i;
    while (a->size < a->total+1){
      a->size *= 2;
    }
    a->array = (void **) realloc(a->array, sizeof(void *) * a->size);
    for (i=size; i<a->size; i++)
    {
      a->array[i] = (void *) malloc(sizeof(char));
    }
    *(char *)((char **)a->array)[a->total] = c;
    a->total=a->total+1;
  }
}

void insert_dyn_array_node(DynArray *a, Node *n)
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

void insert_dyn_array_node_hashed(DynArray *a, Node *n)
{
  if (a->array != NULL){
    int size = a->size;
    if (size < a->total + 1){
      while (size < a->total + 1){
        size *= 2;
      }
      resizeArray(a, size);
      rekeyHashedArray(a);
    }
    findHashKeyAndDoInsert(a, n);
  }
}

Node *lookup_dyn_array_node_hashed(DynArray *a, char c)
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

void remove_dyn_array_node_hashed(DynArray *a, char c)
{
  if (a->array != NULL)
  {
    int size = a->size;
    if (size/2 >= a->total-1 && size > 2)
    {
      while (size/2 >= a->total-1 && size > 2){
	size /= 2;
      }
    }
    findHashKeyAndDoDelete(a, c);
    a->total -= 1;
    resizeArray(a, size);
  }
}

//Remove items based on size, items removed from end
void remove_dyn_array(DynArray *a, int remove){
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
char pop_dyn_array(DynArray *a){
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
void print_dyn_array(DynArray *a){
  int i;
  for (i = 0; i < a->total; i++){
    printf("%c", *(char *)a->array[i]);
  }
  printf("\n");
}

//Convert DynArray to a string
char *dyn_array_to_str(DynArray *a){
  char* return_string = malloc(sizeof(char) * (a->total+1));
  int i;
  for (i = 0; i < a->total; i++){
    return_string[i] = *(char *) a->array[i];
  }
  return_string[i] = '\0';
  return return_string;
}

//Free dynamic array structure
void clear_dyn_array(DynArray *a){
  if (a->size != 0){
    free(a->array);
    a->total = 0;
    a->size = 0;
    a->array = NULL;
  }
}

static void rekey_hashed_array(DynArray *a)
{
  if (a->array != NULL){
    Node **itemsCollected = (Node **) malloc(a->total * sizeof(Node *));
    int i, j = 0;
    a->total = 0;
    for (i = 0; i < a->size; i++) {
      if (a->array[i] != NULL) {
        itemsCollected[j] = ((Node **)a->array)[i];
	a->array[i] = NULL;
        j++;
      }
    }
    for (i = 0; i < j; i++)
    {
      findHashKeyAndDoInsert(a, itemsCollected[i]);
    }
  }
}

static void find_hash_key_and_do_insert(DynArray *a, Node *n)
{
  int j = 0, hashKey = n->key % a->size;
  Node **nodeArray = (Node **) a->array;
  if (nodeArray[hashKey] == NULL){
    nodeArray[hashKey] = n;
    a->total += 1;
  }
  else {
    while (a->array[hashKey] != NULL && ((Node **)a->array)[hashKey]->key != n->key){
      j++;
      hashKey = (n->key + j) % a->size;
    }
    if (nodeArray[hashKey] == NULL)
    {
      nodeArray[hashKey] = n;
    }
    else 
    {
      free(n);
      n = nodeArray[hashKey];
    }
  }
}

static void resize_array(DynArray *a, int size)
{
  int i;
  if (size >= a->size)
  {
    a->array = (void **) realloc(a->array, sizeof(void *) * size);
    for (i = a->size; i < size; i++)
    {
      a->array[i] = NULL;
    }
  }
  else
  {
    for (i = a->size - 1; i >= size; i--)
    {
      if (a->array[i] != NULL){
        free(a->array[i]);
        a->array[i] = NULL;
      }
    }
    a->array = (void **) realloc(a->array, sizeof(void *) * size);
  }
  a->size = size;
}

static int lookup_dyn_array_index_hashed(DynArray *a, char c)
{
  if (a->array != NULL){
    int keyName = c;
    while (((Node **)a->array)[keyName % a->size] != NULL && ((Node **)a->array)[keyName % a->size]->key != c && keyName != c+a->size){
      keyName++;
    }
    if (((Node **)a->array)[keyName % a->size] != NULL && ((Node *)((Node **)a->array)[keyName % a->size])->key == c){
        return keyName % a->size;
    }
    else
      return -1;
  }
  return -1;
}

static void find_hash_key_and_do_delete(DynArray *a, char c)
{
  int indexToDelete = lookupDynArrayIndexHashed(a, c);
  free(a->array[indexToDelete]);
  a->array[indexToDelete] = NULL;
}

