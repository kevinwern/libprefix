// ut_graph.c
// unit test for graph.h library

#include <check.h>
#include <stdio.h>
#include "../src/graph.h"

//TODO, make unit tests use an external word list

START_TEST (ut_graph){
  // Does character hash work properly?
  ck_assert_msg(character_hash('a') == 19, "character_hash of character 'a' should be 19, instead got %d", character_hash('a'));
//  ck_assert_msg(character_hash('a') == 19, NULL);

  Node g;
  //Initalize graph
  init_graph(&g);

  //Store and find single word
  insert_word(&g, "yeah");
  ck_assert_msg(find_word(&g, "yeah") == 1, "Inserted string 'yeah' should be found, but was not");
  ck_assert_msg(find_word(&g, "pipi") == 0, "Absent string 'pipi' shouldn't be found, but something went wrong");

  //No substrings are IN the set, correct?
  ck_assert_msg(find_word(&g, "y") == 0, "String 'y', although a substring of 'yeah', should not be present in the set (found in set)");
  ck_assert_msg(find_word(&g, "ye") == 0, "String 'ye', although a substring of 'yeah', should not be present in the set (found in set)");
  ck_assert_msg(find_word(&g, "yea") == 0, "String 'yea', although a substring of 'yeah', should not be present in the set (found in set)");

  //Add additional words
  insert_word(&g, "yea");
  insert_word(&g, "nono");
  insert_word(&g, "yield");
  insert_word(&g, "year");

  ck_assert_msg(find_word(&g, "yeah") == 1, "String 'yeah' should still be found in the set, even with other inserted elements");
  ck_assert_msg(find_word(&g, "ye") == 0, "String 'ye', although a substring of 'yeah', should not be present in the set (found in set)");
  ck_assert_msg(find_word(&g, "yea") == 1, "Inserted string 'yea', a substring of 'yeah', should now be present in the set (but not found)");
  ck_assert_msg(find_word(&g, "year") == 1, "Inserted string 'year', branching off 'yeah', should now be present in the set (but not found)");
  ck_assert_msg(find_word(&g, "yield") == 1, "Inserted string 'yield', branching off 'yeah', should now be present in the set (but not found)");
  ck_assert_msg(find_word(&g, "nono") == 1, "Inserted string 'nono', should now be present in the set (but not found)");
  
  //delete words
  delete_word(&g, "yea");
  delete_word(&g, "nono");
  delete_word(&g, "not here");

  ck_assert_msg(find_word(&g, "yeah") == 1, "String 'yeah' should still be found in the set, even with other deleted elements");
  ck_assert_msg(find_word(&g, "yea") == 0, "String 'yea', now deleted from the set', should not be present (but was found)");
  ck_assert_msg(find_word(&g, "nono") == 0, "String 'none', now deleted from the set', should not be present (but was found)");
  ck_assert_msg(find_word(&g, "yield") == 1, "String 'yeah' should still be found in the set, even with other deleted elements");
  ck_assert_msg(find_word(&g, "year") == 1, "Inserted string 'year', branching off 'yeah', should now be present in the set (but not found)");

}
END_TEST

Suite *graph_suite (void)
{
  Suite *s = suite_create ("Graph");

  /* Core test case */
  TCase *tc_graph = tcase_create ("unit_test_graph");
  tcase_add_test (tc_graph, ut_graph);
  suite_add_tcase (s, tc_graph);

  return s;
}

int main() {
  int number_failed;
  Suite *s = graph_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all (sr, CK_NORMAL);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
