#include "array.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *array;
  int  size;
  int  total;

} DynArray

void NullArray(DynArray *a, int whatever);

//Initialize array based on size
void initDynArray(DynArray *a, int size){
  a->size = DEFAULT_ARR_SIZE;
  while (array->size<size)
    a->size *= 2;
  a->array = malloc(sizeof(char) * size);
  a->total = size;
  return 0;
}

//Initialize array based on initial string
void initDynArrayStr(DynArray *a, char *str){
  size = strlen(str)
  a->size = DEFAULT_ARR_SIZE;
  while (array->size<size)
    a->size *= 2;
  a->array = malloc(sizeof(char) * size);
  a->total = size;
  return 0;
}
//Insert items into array
void insertDynArray(DynArray *a, char *str);

//Remove items based on size, items removed from end
void removeDynArray(DynArray *a, char *str);

//Free dynamic array structure
void clearDynArray(DynArray *a){
  if a->size > 0

}
~                                    
