// array.h -- DynArray
// A variable-size structure handling any type of variable
#ifndef ARRAY_H
#define ARRAY_H
#define DEFAULT_SIZE 2
#define MIN_SIZE 2
#include "graph.h"
#include "defaultargs.h"
#include "liberrors.h"
#include <wchar.h>
#define init_dyn_array(...) EVALUATE(init_dyn_array, ARGN(__VA_ARGS__))(__VA_ARGS__)

typedef enum ArrayType {
  CONTINUOUS,
  NON_CONTINUOUS
} ArrayType;

typedef struct DynArray {
  ArrayType type;
  void **array;
  int  size;
  int  total;
} DynArray;

// Initialize array based on size
// Default arguments: size = DEFAULT_SIZE, type = CONTINUOUS
int init_dyn_array3(DynArray *a, ArrayType type, int size);
int init_dyn_array2(DynArray *a, ArrayType type);
int init_dyn_array1(DynArray *a);

//Remove last item in array, returning that item
wchar_t pop_dyn_array(DynArray *a);

//Insert single character into array
int append_dyn_array_char(DynArray *a, wchar_t c);

//Insert node into array
int insert_dyn_array_node(DynArray *a, Node* n, int index);

//Return character located at index
wchar_t lookup_dyn_array_char(DynArray *a, int index);

//Lookup node
Node *lookup_dyn_array_node(DynArray *a, int index);

//Remove items based on size, items removed from end
void remove_dyn_array(DynArray *a, int remove);

//Free dynamic array structure
void clear_dyn_array(DynArray *a);

//Convert DynArray to string
wchar_t *dyn_array_to_str(DynArray *a);

//Resize array to different size
static int resize_array(DynArray *a, int size);

//Insert node into hash table
static void find_hash_key_and_do_insert(DynArray *a, Node *n);

//Re-insert items into hashed array
static void rekey_hashed_array(DynArray *a);

//Lookup an array item by key for a hash table
static int lookup_dyn_array_index_hashed(DynArray *a, wchar_t c);

//Delete from hash table key
static void find_hash_key_and_do_delete(DynArray *a, wchar_t c);


#endif
