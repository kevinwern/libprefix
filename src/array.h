// Array.h - dynamically allocated array, for character strings
// Intended for character string storage in graph structure and
// printing graphs based on characters
#ifndef ARRAY_H
#define ARRAY_H
#define DEFAULT_SIZE 1

typedef struct {
  char *array;
  int  size;
  int  total;

} DynArray

//Initialize array based on size
void initDynArray(DynArray *a, int size);

//Initialize array based on initial string
void initDynArrayStr(DynArray *a, char *str);

//Insert items into array
void insertDynArray(DynArray *a, char *str);

//Remove items based on size, items removed from end
void removeDynArray(DynArray *a, char *str);

//Free dynamic array structure
void clearDynArray(DynArray *a);
