// ut_graph.c
// unit test for graphraph.h library
#include <check.h>
#include <stdio.h>
#include "../src/graph.h"

node *graph;

void setup (void) 
{
  graph = alloc_node();
}

void teardown(void)
{
  dealloc_node(graph);
}

START_TEST (ut_graph){
  //Initalize graph
  init_node(graph);
  //Store and find single word
  insert_word(graph, L"yeah");

  ck_assert_msg(find_word(graph, L"yeah") == 1, "Inserted string 'yeah' should be found, but was not");
  ck_assert_msg(find_word(graph, L"pipi") == 0, "Absent string 'pipi' shouldn't be found, but something went wrong");

  //No substrings are IN the set, correct?
  ck_assert_msg(find_word(graph, L"y") == 0, "String 'y', although a substring of 'yeah', should not be present in the set (found in set)");
  ck_assert_msg(find_word(graph, L"ye") == 0, "String 'ye', although a substring of 'yeah', should not be present in the set (found in set)");
  ck_assert_msg(find_word(graph, L"yea") == 0, "String 'yea', although a substring of 'yeah', should not be present in the set (found in set)");

  //Add additional words
  insert_word(graph, L"yea");
  insert_word(graph, L"yield");
  insert_word(graph, L"nono");
  insert_word(graph, L"year");

  ck_assert_msg(find_word(graph, L"yeah") == 1, "String 'yeah' should still be found in the set, even with other inserted elements");
  ck_assert_msg(find_word(graph, L"yep") == 0, "String 'ye', although a substring of 'yeah', should not be present in the set (found in set)");
  ck_assert_msg(find_word(graph, L"yea") == 1, "Inserted string 'yea', a substring of 'yeah', should now be present in the set (but not found)");
  ck_assert_msg(find_word(graph, L"year") == 1, "Inserted string 'year', branching off 'yeah', should now be present in the set (but not found)");
  ck_assert_msg(find_word(graph, L"yield") == 1, "Inserted string 'yield', branching off 'yeah', should now be present in the set (but not found)");
  ck_assert_msg(find_word(graph, L"nono") == 1, "Inserted string 'nono', should now be present in the set (but not found)");
  
  //delete words
  delete_word(graph, L"yea");
  delete_word(graph, L"nono");
  delete_word(graph, L"not here");

  ck_assert_msg(find_word(graph, L"yeah") == 1, "String 'yeah' should still be found in the set, even with other deleted elements");
  ck_assert_msg(find_word(graph, L"yea") == 0, "String 'yea', now deleted from the set', should not be present (but was found)");
  ck_assert_msg(find_word(graph, L"nono") == 0, "String 'none', now deleted from the set', should not be present (but was found)");
  ck_assert_msg(find_word(graph, L"yield") == 1, "String 'yeah' should still be found in the set, even with other deleted elements");
  ck_assert_msg(find_word(graph, L"year") == 1, "Inserted string 'year', branching off 'yeah', should now be present in the set (but not found)");

  clear_node(graph);
}
END_TEST

START_TEST (ut_graph_load_dictionary)
{
  init_node(graph);
  
  FILE *fp = fopen("/usr/share/dict/words", "r");
  wchar_t word[1000];
  
  while (fgetws(word, 80, fp)) 
  {
    word[wcslen(word)-1] = L'\0';
    insert_word(graph, word);
  }
  rewind(fp);
 
  while (fgetws(word, 80, fp)) 
  {
    word[wcslen(word)-1] = L'\0';
     ck_assert_msg(find_word(graph, word) == 1, "Can't find word %ls in full dictionary test\n", word);
  }
  fclose(fp);

  clear_node(graph);
}
END_TEST

Suite *graph_suite (void)
{
  Suite *s = suite_create("Graph");

  /* Core test case */
  TCase *tc_graph = tcase_create("unit_test_graph");
  tcase_add_test(tc_graph, ut_graph);
  tcase_add_checked_fixture(tc_graph, setup, teardown);
  suite_add_tcase(s, tc_graph);
  TCase *tc_graph_load_dictionary = tcase_create ("unit_test_graph_dict");
  tcase_add_test(tc_graph_load_dictionary, ut_graph_load_dictionary);
  tcase_add_checked_fixture(tc_graph_load_dictionary, setup, teardown);
  suite_add_tcase (s, tc_graph_load_dictionary);

  return s;
}

int main() {
  int number_failed;
  Suite *s = graph_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all (sr, CK_NORMAL);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
