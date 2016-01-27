#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

dyn_array *alloc_dyn_array()
{
  dyn_array *new_array = (dyn_array *) malloc(sizeof(dyn_array));
  new_array->size = 0;
  new_array->total = 0;
  new_array->type = UNINITIALIZED;
  new_array->array = NULL;
  return new_array;
}

// Initialize array, optionally based on size and type.
int init_dyn_array3(dyn_array *a, array_type type, int size){
  if (a->type != UNINITIALIZED)
  {
    clear_dyn_array(a);
  }
  int i;
  a->size = MIN_SIZE;
  a->type = type;
  while (a->size<size) {
    a->size *= 2;
  }
  a->total = 0;
  a->array = malloc(sizeof(void *) * a->size);
  for (i = 0; i < size; i++){
    a->array[i] = NULL;
  }
  return 0;
}

int init_dyn_array2(dyn_array *a, array_type type)
{
  return init_dyn_array3(a, type, DEFAULT_SIZE);
}

int init_dyn_array1(dyn_array *a)
{
  return init_dyn_array3(a, CONTINUOUS, DEFAULT_SIZE);
}

// Add character after last assigned member.
int append_dyn_array_char(dyn_array *a, wchar_t c)
{
  if (a->type != CONTINUOUS)
  {
    libprefix_set_error(INCORRECT_ARR_TYPE);
    return -1;
  }
  if (a->array != NULL){
    int size = a->size;
    int i;
    while (a->size < a->total+1){
      a->size *= 2;
    }
    if (size != a->size)
    {
      a->array = (void **) realloc(a->array, sizeof(void *) * a->size);
      for (i=size; i<a->size; i++)
      {
        a->array[i] = (wchar_t *) malloc(sizeof(wchar_t));
      }
    }
    if (a->array[a->total] == NULL) a->array[a->total] = (wchar_t *) malloc(sizeof(wchar_t));
    *(wchar_t *)((wchar_t **)a->array)[a->total] = c;
    a->total=a->total+1;
    return 0;
  }
  else 
  {
    libprefix_set_error(ARR_NOT_INIT);
    return -1;
  }
}

// Insert node at any point in dyn_array
int insert_dyn_array_node(dyn_array *a, node *n, int index)
{
  if (a->type != NON_CONTINUOUS) {
    libprefix_set_error(INCORRECT_ARR_TYPE);
    return -1;
  }
  if (a->array != NULL) {
    if (a->size <= index || index < 0) {
      libprefix_set_error(INVALID_INDEX);
      return -1; 
    }
    if (a->array[index] != NULL) {
      clear_node(a->array[index]);
    }
    else {
      a->total += 1;
    }
    a->array[index] = n;
    return 0;
  }
  else {
    libprefix_set_error(ARR_NOT_INIT);
    return -1;
  }
}

// Lookup character at any point in dyn_array
wchar_t lookup_dyn_array_char(dyn_array *a, int index)
{
  if (a->array != NULL) {
    if (a->size <= index || index < 0) {
      libprefix_set_error(INVALID_INDEX);
      return -1;
    }
    else {
      return *(wchar_t*) a->array[index];
    }
  }
  else {
    libprefix_set_error(ARR_NOT_INIT);
    return -1;
  }
}

// Lookup node at any point in dyn_array
node *lookup_dyn_array_node(dyn_array *a, int index)
{
  if (a->array != NULL) {
    if (a->size <= index || index < 0) {
      libprefix_set_error(INVALID_INDEX);
      return NULL;
    }
    else {
      return (node *)(((node **)a->array)[index]);
    }
  }
  else {
    libprefix_set_error(ARR_NOT_INIT);
    return NULL;
  }
}

// Delete node from any point in dyn_array
int delete_dyn_array_node(dyn_array *a, int index)
{
  if (a->array != NULL) {
    if (a->size <= index || index < 0) {
      libprefix_set_error(INVALID_INDEX);
      return -1;
    }
    else if (a->array[index] == NULL) {
      libprefix_set_error(KEY_NOT_FOUND);
      return -1;
    }
    else {
      free(a->array[index]);
      a->array[index] = NULL;
      a->total -= 1;
      return 0;
    }
  }
  else {
    libprefix_set_error(ARR_NOT_INIT);
    return -1;
  }
}

// Delete node from any point in char
int delete_dyn_array_char(dyn_array *a, int index)
{
  return delete_dyn_array_node(a, index);
}

//Remove items based on size, items removed from end
void remove_dyn_array(dyn_array *a, int remove){
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
wchar_t pop_dyn_array(dyn_array *a){
  if (a->total == 0) {
    libprefix_set_error(INSUFFICIENT_TOTAL);
    return -1;
  }

  if (a->array != NULL) {
    int size = a->size;
    a->total = a->total-1;
    wchar_t toReturn = *(wchar_t *) a->array[a->total];
    while (size / 2 >= a->total  && size > MIN_SIZE){
      size /= 2;
    }
    resize_array(a, size);
    return toReturn;
  }
  else {
    libprefix_set_error(ARR_NOT_INIT);
    return -1;
  }
}

// Convert dyn_array to a string
wchar_t *dyn_array_to_str(dyn_array *a)
{
  if (a->type != CONTINUOUS) {
    libprefix_set_error(INCORRECT_ARR_TYPE);
    return NULL;
  }
  wchar_t *return_string = malloc(sizeof(wchar_t) * (a->total+1));
  int i;
  for (i = 0; i < a->total; i++){
    return_string[i] = *((wchar_t **) a->array)[i];
  }
  return_string[i] = '\0';
  return return_string;
}

// Free dynamic array structure
void clear_dyn_array(dyn_array *a)
{
  int i;
  if (a->type == CONTINUOUS) {
    for (i = 0; i < a->size; i++) {
      free(a->array[i]);
    }
  }
  else {
    for (i = 0; i < a->size; i++) {
      if (a->array[i] != NULL) {
        clear_node(a->array[i]);
        dealloc_node(a->array[i]);
      }
    }
  }
  free(a->array);
  a->size = 0;
  a->total = 0;
  a->type = UNINITIALIZED;
  a->array = NULL;
}

void dealloc_dyn_array(dyn_array *a)
{
  if (a->array != NULL)
  {
    free(a->array);
  }
  free(a);
}

static int resize_array(dyn_array *a, int size)
{
  int i;
  if (size < 0) {
    libprefix_set_error(INVALID_SIZE);
    return -1;
  }
  if (size >= a->size) {
    a->array = realloc(a->array, sizeof(void *) * size);
    for (i = a->size; i < size; i++) {
       a->array[i] = NULL;
    }
  }
  else {
    for (i = a->size - 1; i >= size; i--) {
      if (a->array[i] != NULL) {
        free(a->array[i]);
        a->array[i] = NULL;
      }
    }
    a->array = realloc(a->array, sizeof(void *) * size);
  }
  a->size = size;
  return 0;
}
