// array.h
// assigning string length based on characters
#ifndef ARRAY_H
#define ARRAY_H
#define DEFAULT_SIZE 1

typedef struct {
  char *array;
  int  size;
  int  total;

} DynArray;

//Make array null
void nullDynArray(DynArray *a);

//Initialize array based on size
int initDynArray(DynArray *a, int size);

//Initialize array based on initial string
int initDynArrayStr(DynArray *a, char *str);

//Insert items into array
void insertDynArray(DynArray *a, char *str);

//Remove items based on size, items removed from end
void removeDynArray(DynArray *a, int remove);

//Free dynamic array structure
void clearDynArray(DynArray *a);

#endif
