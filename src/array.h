// array.h -- DynArray
// A variable-size structure handling any type of variable
#ifndef ARRAY_H
#define ARRAY_H
#define DEFAULT_SIZE 2
#include "graph.h"

enum ArrayType {
  CONTINUOUS;
  NON_CONTINUOUS;
};

typedef struct DynArray {
  ArrayType type;
  void **array;
  int  size;
  int  total;
} DynArray;

//Initialize array based on size
int init_dyn_array(DynArray *a, int size);

//Initialize array for hash table
void init_dyn_array_hashed(DynArray *a);

//Remove last item in array, returning that item
char pop_dyn_array(DynArray *a);

//Insert single character into array
void insert_dyn_array_char(DynArray *a, char c);

//Insert node into array hashed (for graph)
void insert_dyn_array_node_hashed(DynArray *a, Node* n);

//Lookup char
Node *lookup_dyn_array_node_hashed(DynArray *a, char key);

//Remove items based on size, items removed from end
void remove_dyn_array(DynArray *a, int remove);

//Free dynamic array structure
void clear_dyn_array(DynArray *a);

//Print contents of DynArray
void print_dyn_array(DynArray *a);

//Convert DynArray to string
char *dyn_array_to_str(DynArray *a);

//Print contents of DynArray of nodes
char *dyn_array_to_str_node(DynArray *a);

static void resize_array(DynArray *a, int size);

static void find_hash_key_and_do_insert(DynArray *a, Node *n);

static void rekey_hashedarray(DynArray *a);

static int lookup_dyn_array_index_hashed(DynArray *a, char c);

static void find_hash_key_and_do_delete(DynArray *a, char c);

void remove_dyn_array_node_hashed(DynArray *a, char c);

#endif
