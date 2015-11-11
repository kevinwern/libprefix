// ut_hashtable.c
// unit test for HashTable wrapper for DynArray

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/array.h"
#include "../src/hashtable.h"
#include "../src/graph.h"

HashTable *test_hash_table;

void setup (void)
{
  test_hash_table = alloc_hash_table();
}

void teardown (void)
{
  dealloc_hash_table(test_hash_table);
}

START_TEST (ut_hash_table_init)
{
  init_hash_table(test_hash_table, DEFAULT_SIZE);
  clear_hash_table(test_hash_table);
}
END_TEST

START_TEST (ut_hash_table_insert_and_lookup)
{
  init_hash_table(test_hash_table, DEFAULT_SIZE);
  wchar_t c;
  int i;
  Node *result;
  for (c = L'a'; c <= L'z'; c++)
  {
    insert_node(test_hash_table, c);
  }

  for (c = L'a'; c <= L'z'; c++)
  {
    result = lookup_node(test_hash_table, c);
    if (result != NULL) ck_assert_msg(result->key == c, "%c != %c", result->key, c);
    else ck_abort_msg("Couldn't find character %c", c);
  }
  ck_assert_msg(test_hash_table->array->total == 26);
  ck_assert_msg(test_hash_table->array->size == 32);
  clear_hash_table(test_hash_table);
}
END_TEST

START_TEST (ut_hash_table_insert_and_delete)
{
  init_hash_table(test_hash_table, DEFAULT_SIZE);
  char c;
  int i;
  Node *result;
  for (c = 'a'; c <= 'z'; c++)
  {
    insert_node(test_hash_table, c);
  }
  for (c = 'a'; c <= 'z'; c++)
  {
    delete_node(test_hash_table, c);
  }
  ck_assert_msg(test_hash_table->array->total == 0, "%d\n", test_hash_table->array->total);
  ck_assert_msg(test_hash_table->array->size == 2, "%d\n", test_hash_table->array->size);
  clear_hash_table(test_hash_table);
}
END_TEST

Suite *hash_table_suite(void)
{
  Suite *s = suite_create("HashTable");

  TCase *tc_hash_table = tcase_create("ut_hash_table_init");
  tcase_add_checked_fixture(tc_hash_table, setup, teardown);
  tcase_add_test(tc_hash_table, ut_hash_table_init);
  suite_add_tcase(s, tc_hash_table);
  TCase *tc_hash_table_insert_and_lookup = tcase_create("ut_hash_table_insert_and_lookup");
  tcase_add_test(tc_hash_table_insert_and_lookup, ut_hash_table_insert_and_lookup);
  tcase_add_checked_fixture(tc_hash_table_insert_and_lookup, setup, teardown);
  suite_add_tcase(s, tc_hash_table_insert_and_lookup);
/*  TCase *tc_hash_table_insert_and_delete = tcase_create("ut_hash_table_insert_and_delete");
  tcase_add_test(tc_hash_table_insert_and_delete, ut_hash_table_insert_and_delete);
  tcase_add_checked_fixture(tc_hash_table_insert_and_delete, setup, teardown);
  suite_add_tcase(s, tc_hash_table_insert_and_delete);*/
  return s;
}

int main() 
{
  int number_failed;
  SRunner *sr = srunner_create(hash_table_suite());
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

