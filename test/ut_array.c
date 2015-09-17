// ut_array.c
// unit test for DynArray (dynamic array) Helper Library

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/array.h"
#include "../src/graph.h"

DynArray test_array;

void setup (void)
{
  init_dyn_array(&test_array);
}

void teardown (void)
{
  clear_dyn_array(&test_array);
}

START_TEST (ut_array_init)
{
  DynArray array, array2, array3;
  int custom_size = 8;
  init_dyn_array(&array);
  ck_assert_msg(array.size == DEFAULT_SIZE,
    "One-parameter call to init_dyn_array did not set size to DEFAULT_SIZE. Got size %d.", array.size);
  ck_assert_msg(array.type == CONTINUOUS,
    "One-parameter call to init_dyn_array did not set type to CONTINUOUS.");
  init_dyn_array(&array2, NON_CONTINUOUS);
  ck_assert_msg(array2.size == DEFAULT_SIZE,
    "Two-parameter call to init_dyn_array did not set size to DEFAULT_SIZE. Got size %d.", array.size);
  ck_assert_msg(array2.type == NON_CONTINUOUS,
    "Two-parameter call to init_dyn_array did not set type to prescribed NON_CONTINUOUS.");
  init_dyn_array(&array3, NON_CONTINUOUS, custom_size);
  ck_assert_msg(array3.size == custom_size,
    "Three-parameter call to init_dyn_array did not set size to prescribed value %d. Got size %d.", 
    custom_size, array.size);
  ck_assert_msg(array3.type == NON_CONTINUOUS,
    "Three-parameter call to init_dyn_array did not set type to prescribed NON_CONTINUOUS.");
}
END_TEST

START_TEST (ut_array_append_char)
{
  wchar_t character_to_insert = 'c', returned_character;
  int expected_index = 0;
  append_dyn_array_char(&test_array, character_to_insert);
  returned_character = lookup_dyn_array_char(&test_array, expected_index);
  ck_assert_msg(returned_character == character_to_insert,
    "Insert failed, expected character '%c' at index %d. Got '%c'",
    character_to_insert, expected_index, returned_character); 
}
END_TEST

START_TEST (ut_array_append_pop_char)
{
  wchar_t character_to_insert = 'c', returned_character;
  int expected_index = 0;
  append_dyn_array_char(&test_array, character_to_insert);
  returned_character = pop_dyn_array(&test_array);
  ck_assert_msg(returned_character == character_to_insert,
    "Pop failed, expected character '%c' at index %d. Got '%c'",
    character_to_insert, expected_index, returned_character); 
}
END_TEST

START_TEST (ut_array_insert_node)
{
  init_dyn_array(&test_array, NON_CONTINUOUS);
  int index_to_add = 1;
  Node node;
  Node *test_node;
  insert_dyn_array_node(&test_array, &node, index_to_add);
  test_node = lookup_dyn_array_node(&test_array, index_to_add);
  ck_assert_msg(test_node == &node,
    "Node inserted was not found");
}
END_TEST

START_TEST (ut_array_to_str)
{
  wchar_t i;
  int j;
  wchar_t expected[27];
  wchar_t *result;
  for (i = 'a', j = 0; i <= 'z'; i++, j++)
  {
    append_dyn_array_char(&test_array, i);
    expected[j] = i;
  }
  expected[j] = '\0';
  result = dyn_array_to_str(&test_array);
  ck_assert_msg(strcmp(expected, result) == 0, 
    "Array string does not match expected value '%s'. Got '%s'", expected, result);
  ck_assert_msg(test_array.size == 32);
}
END_TEST

Suite *array_suite(void)
{
  Suite *s = suite_create("DynArray");

  TCase *tc_dyn_array = tcase_create("ut_array_init");
  tcase_add_test(tc_dyn_array, ut_array_init);
  suite_add_tcase(s, tc_dyn_array);
  TCase *tc_append_char = tcase_create("ut_array_append_char");
  tcase_add_test(tc_append_char, ut_array_append_char);
  suite_add_tcase(s, tc_append_char);
  tcase_add_checked_fixture(tc_append_char, setup, teardown);
  TCase *tc_append_pop_char = tcase_create("ut_array_append_pop_char");
  tcase_add_test(tc_append_pop_char, ut_array_append_pop_char);
  suite_add_tcase(s, tc_append_pop_char);
  tcase_add_checked_fixture(tc_append_pop_char, setup, teardown);
  TCase *tc_insert_node = tcase_create("ut_array_insert_node");
  tcase_add_test(tc_insert_node, ut_array_insert_node);
  suite_add_tcase(s, tc_insert_node);
  tcase_add_checked_fixture(tc_insert_node, setup, teardown);
  TCase *tc_to_str = tcase_create("ut_array_to_str");
  tcase_add_test(tc_to_str, ut_array_to_str);
  tcase_add_checked_fixture(tc_to_str, setup, teardown);
  suite_add_tcase(s, tc_to_str);
  return s;
}

int main() 
{
  int number_failed;
  SRunner *sr = srunner_create(array_suite());
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

