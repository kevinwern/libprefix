#include <stdio.h>
#include "graph.h"


int main() {

//  char* word;

//  scanf("%s" , word);
//  printf("%s\n", word);


  Node g;
  init_graph(&g);
  insert_word(&g, "yeah");
  insert_word(&g, "yea");
  insert_word(&g,  "yep");
  delete_word(&g,  "yeah");


  printf("%d\n", find_word(&g, "yeah"));
  printf("%d\n", find_word(&g, "yup"));
  printf("%d\n", find_word(&g, "yep"));

  return 0;

}
