// ut_hashtable.c
// unit test for HashTable wrapper for DynArray

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/array.h"
#include "../src/hashtable.h"
#include "../src/graph.h"

HashTable test_hash_table;

void setup (void)
{
  init_hash_table(&test_hash_table, DEFAULT_SIZE);
}

void teardown (void)
{
  clear_hash_table(&test_hash_table);
}

START_TEST (ut_hash_table_init)
{
  init_hash_table(&test_hash_table, DEFAULT_SIZE);
}
END_TEST

START_TEST (ut_hash_table_insert_and_lookup)
{
  init_hash_table(&test_hash_table, DEFAULT_SIZE);
  char c;
  Node *result;
  for (c = 'a'; c <= 'b'; c++)
  {
    insert_node(&test_hash_table, c);
  }

  for (int i = 0; i < 1; i++)
  {
    result = (Node *) ((Node **)test_hash_table.array)[i];
    if (result != NULL)
      printf("%c\n", result->key);
  }

/*  for (c = 'a'; c <= 'c'; c++)
  {
    result = lookup_node(&test_hash_table, c);
    if (result != NULL) ck_assert_msg(result->key == c, "%c != %c", result->key, c);
    else ck_abort_msg("Couldn't find character %c", c);
  }*/
}
END_TEST

Suite *hash_table_suite(void)
{
  Suite *s = suite_create("HashTable");

  TCase *tc_hash_table = tcase_create("ut_hash_table_init");
  tcase_add_test(tc_hash_table, ut_hash_table_init);
  suite_add_tcase(s, tc_hash_table);
  tcase_add_checked_fixture(tc_hash_table, setup, teardown);
  TCase *tc_hash_table_insert_and_lookup = tcase_create("ut_hash_table_insert_and_lookup");
  tcase_add_test(tc_hash_table_insert_and_lookup, ut_hash_table_insert_and_lookup);
  suite_add_tcase(s, tc_hash_table_insert_and_lookup);
  TCase *tc_hash_table2 = tcase_create("ut_hash_table_init");
  tcase_add_test(tc_hash_table2, ut_hash_table_init);
  suite_add_tcase(s, tc_hash_table2);
  tcase_add_checked_fixture(tc_hash_table2, setup, teardown);
  return s;
}

int main() 
{
  int number_failed;
  SRunner *sr = srunner_create(hash_table_suite());
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

