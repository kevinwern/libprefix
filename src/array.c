#include "array.h"
#include <stdlib.h>

typedef struct {
  char *array;
  int  size;
  int  total;

} DynArray

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

}

//Insert items into array
void insertDynArray(DynArray *a, char *str);

//Remove items based on size, items removed from end
void removeDynArray(DynArray *a, char *str);

//Free dynamic array structure
void clearDynArray(DynArray *a);
~                                    
