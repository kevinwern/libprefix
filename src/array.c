#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

DynArray *alloc_dyn_array()
{
  DynArray *new_array = malloc(sizeof(DynArray));
  LIBPREFIX_ASSERT(new_array != NULL, MALLOC_FAILED, NULL);
  new_array->size = 0;
  new_array->total = 0;
  new_array->type = UNINITIALIZED;
  new_array->array = NULL;
  return new_array;
}

// Initialize array, optionally based on size and type.
int init_dyn_array4(DynArray *a, ArrayType type, size_t size,
                    size_t member_size)
{
  LIBPREFIX_ASSERT(size % 2 == 0 && size > 0, INVALID_SIZE);
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
  a->member_size = member_size;
  a->total = 0;
  a->array = malloc(member_size * a->size);
  LIBPREFIX_ASSERT(a->array != NULL, MALLOC_FAILED);
  for (i = 0; i < size; i++){
    a->array[i] = NULL;
  }
  return 0;
}

int init_dyn_array3(DynArray *a, ArrayType type, size_t member_size)
{
  return init_dyn_array4(a, type, DEFAULT_SIZE, member_size);
}

int init_dyn_array2(DynArray *a, size_t member_size)
{
  return init_dyn_array4(a, CONTINUOUS, DEFAULT_SIZE, member_size);
}

// Add character after last assigned member.
int append_dyn_array_char(DynArray *a, wchar_t c)
{
  LIBPREFIX_ASSERT(a->type != UNINITIALIZED, ARR_NOT_INIT);
  LIBPREFIX_ASSERT(a->type == CONTINUOUS, INCORRECT_ARR_TYPE);

  int size = a->size;
  int i;
  while (a->size <= a->total){
    a->size *= 2;
  }
  if (size != a->size)
  {
    a->array = realloc(a->array, a->member_size * a->size);
    for (i=size; i<a->size; i++)
    {
      a->array[i] = malloc(sizeof(wchar_t));
      LIBPREFIX_ASSERT(a->array[i] != NULL, MALLOC_FAILED);
    }
  }

  if (a->array[a->total] == NULL) 
  {
      a->array[a->total] = malloc(sizeof(wchar_t));
      LIBPREFIX_ASSERT(a->array[a->total] != NULL, MALLOC_FAILED);
  }
  *((wchar_t **) a->array)[a->total] = c;
  a->total=a->total+1;
  return 0;
}

// Add character after last assigned member.
int append_dyn_array_node(DynArray *a, Node *n)
{
  LIBPREFIX_ASSERT(a->type != UNINITIALIZED, ARR_NOT_INIT);
  LIBPREFIX_ASSERT(a->type == CONTINUOUS, INCORRECT_ARR_TYPE);

  int size = a->size;
  int i;
  while (a->size < a->total+1){
    a->size *= 2;
  }
  if (size != a->size)
  {
    a->array = realloc(a->array, sizeof(Node *) * a->size);
    for (i=size; i<a->size; i++)
    {
      a->array[i] = malloc(sizeof(Node));
      LIBPREFIX_ASSERT(a->array[i] != NULL, MALLOC_FAILED);
    }
  }

  if (a->array[a->total] == NULL) 
  {
      a->array[a->total] = malloc(sizeof(Node));
      LIBPREFIX_ASSERT(a->array[a->total] != NULL, MALLOC_FAILED);
  }
  a->array[a->total] = n;
  a->total=a->total+1;
  return 0;
}

// Insert node at any point in DynArray
int insert_dyn_array_node(DynArray *a, Node *n, int index)
{
  LIBPREFIX_ASSERT(a->type != UNINITIALIZED, ARR_NOT_INIT);
  LIBPREFIX_ASSERT(a->type == NON_CONTINUOUS, INCORRECT_ARR_TYPE);

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

// Lookup character at any point in DynArray
wchar_t lookup_dyn_array_char(DynArray *a, int index)
{
  LIBPREFIX_ASSERT(a->type != UNINITIALIZED, ARR_NOT_INIT);
  LIBPREFIX_ASSERT(index < a->size || index >= 0, INVALID_INDEX);

  return *((wchar_t **) a->array)[index];
}

// Lookup Node at any point in DynArray
Node *lookup_dyn_array_node(DynArray *a, int index)
{
  LIBPREFIX_ASSERT(a->type != UNINITIALIZED, ARR_NOT_INIT, NULL);
  LIBPREFIX_ASSERT(a->type == NON_CONTINUOUS, INCORRECT_ARR_TYPE, NULL);
  LIBPREFIX_ASSERT(index < a->size || index >= 0, INVALID_INDEX, NULL);
  return a->array[index];
}

// Delete Node from any point in DynArray
int delete_dyn_array_node(DynArray *a, int index)
{
  LIBPREFIX_ASSERT(a->type != UNINITIALIZED, ARR_NOT_INIT);
  LIBPREFIX_ASSERT(a->type == NON_CONTINUOUS, INCORRECT_ARR_TYPE);
  LIBPREFIX_ASSERT(index < a->size || index >= 0, INVALID_INDEX);
  LIBPREFIX_ASSERT(a->array[index] != NULL, KEY_NOT_FOUND);

  clear_node(a->array[index]);
  dealloc_node(a->array[index]);
  a->array[index] = NULL;
  a->total -= 1;
  return 0;
}

// Delete Node from any point in char
int delete_dyn_array_char(DynArray *a, int index)
{
  LIBPREFIX_ASSERT(a->type != UNINITIALIZED, ARR_NOT_INIT);
  LIBPREFIX_ASSERT(index < a->size || index >= 0, INVALID_INDEX);
  LIBPREFIX_ASSERT(a->array[index] != NULL, KEY_NOT_FOUND);

  return delete_dyn_array_node(a, index);
}

//Remove items based on size, items removed from end
void remove_dyn_array(DynArray *a, int remove)
{
  int newsize = a->total-remove;
  if (a->array != NULL && newsize >= 0){
    while (a->size / 2 > newsize){
      a->size /= 2;
    }
    a->total = newsize;
    a->array = realloc(a->array, sizeof(Node *) * a->size);
  }
}

//returns last character in array
wchar_t pop_dyn_array(DynArray *a)
{
  LIBPREFIX_ASSERT(a->type != UNINITIALIZED, ARR_NOT_INIT);
  LIBPREFIX_ASSERT(a->total > 0, INSUFFICIENT_TOTAL);

  int size = a->size;
  a->total = a->total-1;
  wchar_t to_return = *((wchar_t **) a->array)[a->total];
  while (size / 2 >= a->total  && size > MIN_SIZE){
    size /= 2;
  }
  resize_array(a, size);
  return to_return;
}

Node *pop_dyn_array_node(DynArray *a)
{
  LIBPREFIX_ASSERT(a->type != UNINITIALIZED, ARR_NOT_INIT, NULL);
  LIBPREFIX_ASSERT(a->total > 0, INSUFFICIENT_TOTAL, NULL);

  int size = a->size;
  a->total = a->total-1;
  Node *to_return = a->array[a->total];
  while (size / 2 >= a->total  && size > MIN_SIZE){
    size /= 2;
  }
  resize_array(a, size);
  return to_return;
}

// Convert DynArray to a string
wchar_t *dyn_array_to_str(DynArray *a)
{
  LIBPREFIX_ASSERT(a->type != UNINITIALIZED, ARR_NOT_INIT, NULL);
  LIBPREFIX_ASSERT(a->type == CONTINUOUS, INCORRECT_ARR_TYPE, NULL);

  wchar_t *return_string = malloc(sizeof(wchar_t) * (a->total+1));
  LIBPREFIX_ASSERT(return_string != NULL, MALLOC_FAILED, NULL);
  int i;
  for (i = 0; i < a->total; i++){
    return_string[i] = *((wchar_t **) a->array)[i];
  }
  return_string[i] = '\0';
  return return_string;
}

// Free dynamic array structure
void clear_dyn_array(DynArray *a)
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

void dealloc_dyn_array(DynArray *a)
{
  if (a->array != NULL)
  {
    free(a->array);
  }
  free(a);
}

static int resize_array(DynArray *a, int size)
{
  LIBPREFIX_ASSERT(a->type != UNINITIALIZED, ARR_NOT_INIT);
  LIBPREFIX_ASSERT(size >= MIN_SIZE && size % 2 == 0, INVALID_SIZE);

  int i;
  if (size >= a->size) {
    a->array = realloc(a->array, a->member_size * size);
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
    a->array = realloc(a->array, a->member_size * size);
  }
  a->size = size;
  return 0;
}
