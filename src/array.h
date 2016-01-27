// array.h -- dyn_array
// A dynamic-size structure handling any data type

#ifndef ARRAY_H
#define ARRAY_H
#define DEFAULT_SIZE 2
#define MIN_SIZE 2
#include "graph.h"
#include "defaultargs.h"
#include "liberrors.h"
#include <wchar.h>
#define init_dyn_array(...) EVALUATE(init_dyn_array, ARGN(__VA_ARGS__))(__VA_ARGS__)

typedef enum array_type {
  UNINITIALIZED,
  CONTINUOUS,
  NON_CONTINUOUS
} array_type;

typedef struct dyn_array {
  array_type type;
  void **array;
  int  size;
  int  total;
} dyn_array;

dyn_array *alloc_dyn_array();
void dealloc_dyn_array(dyn_array *a);

// Initialize array based on size
// Default arguments: size = DEFAULT_SIZE, type = CONTINUOUS
int init_dyn_array3(dyn_array *a, array_type type, int size);
int init_dyn_array2(dyn_array *a, array_type type);
int init_dyn_array1(dyn_array *a);

//Remove last item in array, returning that item
wchar_t pop_dyn_array(dyn_array *a);

//Insert single character into array
int append_dyn_array_char(dyn_array *a, wchar_t c);

//Insert node into array
int insert_dyn_array_node(dyn_array *a, node* n, int index);

//Return character located at index
wchar_t lookup_dyn_array_char(dyn_array *a, int index);

//Lookup node
node *lookup_dyn_array_node(dyn_array *a, int index);

//Remove items based on size, items removed from end
void remove_dyn_array(dyn_array *a, int remove);

//Free dynamic array structure
void clear_dyn_array(dyn_array *a);

//Convert dyn_array to string
wchar_t *dyn_array_to_str(dyn_array *a);

//Resize array to different size
static int resize_array(dyn_array *a, int size);

//Insert node into hash table
static void find_hash_key_and_do_insert(dyn_array *a, node *n);

//Re-insert items into hashed array
static void rekey_hashed_array(dyn_array *a);

//Lookup an array item by key for a hash table
static int lookup_dyn_array_index_hashed(dyn_array *a, wchar_t c);

//Delete from hash table key
static void find_hash_key_and_do_delete(dyn_array *a, wchar_t c);

#endif
