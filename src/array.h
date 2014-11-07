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

//Remove last item in array, returning that item
char popDynArray(DynArray *a);

//Insert items into array
void insertDynArrayStr(DynArray *a, char *str);

//Insert single character into array
void insertDynArray(DynArray *a, char c);

//Remove items based on size, items removed from end
void removeDynArray(DynArray *a, int remove);

//Free dynamic array structure
void clearDynArray(DynArray *a);

#endif
