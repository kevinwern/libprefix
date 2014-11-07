// libprefix array.c
// Implemented functions for array.h

#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Initialize all array values to empty
void nullDynArray(DynArray *a){
  a->size = 0;
  a->total = 0;
  a->array = NULL;
}

//Initialize array based on size
int initDynArray(DynArray *a, int size){
  a->size = DEFAULT_SIZE;
  while (a->size<size)
    a->size *= 2;
  a->array = malloc(sizeof(char) * a->size);
  a->total = 0;
  return 0;
}

//Initialize array based on initial string
int initDynArrayStr(DynArray *a, char *str){
  int size = strlen(str);
  a->size = DEFAULT_SIZE;
  while (a->size<size)
    a->size *= 2;
  a->array = malloc(sizeof(char) * size);
  a->total = size;

  int i;
  for(i = 0; i<size; i++){
    a->array[i]=str[i];
  }
  return 0;
}

//Insert items into array
void insertDynArrayStr(DynArray *a, char *str){
  int addsize = strlen(str);
  if (a->array != NULL){
    while (a->size < a->total+addsize){
      a->size *= 2;
    }
    a->array = realloc(a->array, sizeof(char) * a->size);
    int i;

    for (i = 0; i <addsize; i++){
      a->array[i+a->size] = str[i];
    }
    a->total = a->total+addsize;
  }
}

void insertDynArray(DynArray *a, char c){
  if (a->array != NULL){
    while (a->size < a->total+1){
      a->size *= 2;
    }
    a->array = realloc(a->array, sizeof(char) * a->size);
    a->array[a->total] = c;
    a->total=a->total+1;
  }
}

//Remove items based on size, items removed from end
void removeDynArray(DynArray *a, int remove){
  int newsize = a->total-remove;
  if (a->array != NULL && newsize >= 0){
    while (a->size / 2 > newsize){
      a->size /= 2;
    }
    a->total = newsize;
    a->array = realloc(a->array, sizeof(char) * a->size);
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
    char toReturn = a->array[a->total-1];
    a->total = newsize;
    a->array = realloc(a->array, sizeof(char) * a->size);
    return toReturn;
  }
}

//Print contents of a DynArray
void printDynArray(DynArray *a){
  int i;
  for (i = 0; i < a->total; i++){
    printf("%c",a->array[i]);
  }
  printf("\n");
}

//Convert DynArray to a string
char *DynArraytoStr(DynArray *a){
  char return_string[a->total+1];

  int i;
  for (i = 0; i < a->total; i++){
    return_string[i] = a->array[i];
  }
  return_string[i] = '\0';
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
