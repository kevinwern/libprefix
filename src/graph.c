// Graph.c
// Set implemented string comparison
#include <stdlib.h>
#include "graph.h"
#include "liberrors.h"

// Look up a given word in the set
// Params: a node, a word
int find_word (Node *graph, wchar_t *word){
  Node *searchPointer = graph;
  while (*word != L'\0' && searchPointer != NULL){
     searchPointer = lookup_node((HashTable *)(searchPointer->next), *word);
     word++;
  }
  if (*word != L'\0' || searchPointer == NULL)
    return 0;
  else
    return searchPointer->isword;
}

static Node *find_word_node(Node *graph, wchar_t *word){
  Node *searchPointer = graph;
  while (*word != L'\0' && searchPointer != NULL){
     searchPointer = lookup_node((HashTable *)(searchPointer->next), *word);
     word++;
  }
  if (*word != L'\0' || searchPointer == NULL)
    return NULL;
  else {
    return searchPointer;
  }
}

// Insert a new word into the set
// Params: a node, a word
int insert_word (Node *graph, wchar_t *word)
{
  Node *searchPointer = graph;
  while (*word != L'\0'){
    insert_node((HashTable *)(searchPointer->next), *word);
    searchPointer = lookup_node((HashTable *)(searchPointer->next), *word);
    word++;
  }
  searchPointer->isword = 1;
  return 0;
}

// Remove a word in the set
// Params: a node, a word
int delete_word (Node *graph, wchar_t *word)
{
  Node *lastwordnode = NULL, *searchPointer = graph;
  while (*word != L'\0' && searchPointer != NULL){
    if (searchPointer->isword && ((HashTable *)(searchPointer->next))->array->total == 1){
      lastwordnode = searchPointer;
    }
    else if (((HashTable *)(searchPointer->next))->array->total > 1) {
      lastwordnode = NULL;
    }
    searchPointer = lookup_node((HashTable *)(searchPointer->next), *word);
    word++;
  }
  if (searchPointer == NULL)
    return 1;
  searchPointer->isword = 0;
  if (lastwordnode != NULL){
    clear_node(lastwordnode);
    dealloc_node(lastwordnode);
  }
  return 0;
}

PrefixResult *search_prefix(Node *graph, wchar_t *search_string)
{
  Node *search_result_root = find_word_node(graph, search_string);
  DynArray *current_string = alloc_dyn_array();
  PrefixResult *result = NULL;
  init_dyn_array(current_string);
  while (*search_string != L'\0')
  {
    append_dyn_array_char(current_string, *search_string);
    search_string++;
  }
  if (get_permutations(search_result_root, current_string, &result) == 0) {
    clear_dyn_array(current_string);
    dealloc_dyn_array(current_string);
    return result;
  }
  else {
    return NULL;
  }
}

static int get_permutations(Node *location, DynArray *current_string, PrefixResult **collection)
{
  HashTable *current_hash_table = (HashTable *)(location->next);
  DynArray *internal_array = current_hash_table->array;
  if (location->isword)
  {
    PrefixResult *new_result = malloc(sizeof(PrefixResult));
    LIBPREFIX_ASSERT(new_result != NULL, MALLOC_FAILED)
    new_result->next = *collection;
    new_result->word = dyn_array_to_str(current_string);
    *collection = new_result;
  }
  if (is_leaf(location)) {
    return 0;
  }
  else {
    int i;
    for (i = 0; i < internal_array->size; i++)
    {
      Node *next_node = lookup_dyn_array_node(internal_array, i);
      if (next_node != NULL) {
        append_dyn_array_char(current_string, next_node->key);
        if (get_permutations(next_node, current_string, collection) == 0) {
          pop_dyn_array(current_string);
        }
        else {
          return -1;
        }
      }
    }
  }
  return 0;
}
