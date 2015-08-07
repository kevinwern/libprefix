// ut_array.c
// unit test for DynArray (dynamic array) Helper Library

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/array.h"
//#define TEST_SIZE 5
//#define TEST_STRING "peanuts"

START_TEST (ut_array_init_str_works){
  DynArray array;
  initDynArrayStr(&array, "peanut");
  ck_assert_msg(array.size == 8);
  ck_assert_msg(array.total == 6);

}
END_TEST

START_TEST (ut_array_init_size_works)
{
  DynArray array;
  initDynArray(&array, 3);
  ck_assert_msg(array.total == 0);
  ck_assert_msg(array.size == 2);
}
END_TEST

START_TEST (ut_array_init_and_insert_char_works)
{
  DynArray array;
  initDynArrayStr(&array, "peanut");
  insertDynArray(&array, 's');
  char *arrayString = DynArrayToStr(&array);
  ck_assert_msg(strcmp(arrayString, "peanuts") == 0, arrayString);
}
END_TEST

START_TEST (ut_array_init_and_add_string_works)
{
  DynArray array;
  initDynArrayStr(&array, "peanut");
  insertDynArrayStr(&array, "examplestring");
  char *arrayString = DynArrayToStr(&array);
  ck_assert_msg(strcmp(arrayString, "peanutexamplestring") == 0, arrayString);
}
END_TEST 

START_TEST (ut_array_init_and_remove_char_works)
{
  DynArray array;
  initDynArrayStr(&array, "peanut");
  removeDynArray(&array, 1);
  char *arrayString = DynArrayToStr(&array);
  ck_assert_msg(strcmp(arrayString, "peanu") == 0, arrayString);

  removeDynArray(&array, 4);
  arrayString = DynArrayToStr(&array);
  ck_assert_msg(strcmp(arrayString, "p") == 0, arrayString);
}
END_TEST

START_TEST (ut_array_init_and_pop_works)
{
  DynArray array;
  initDynArrayStr(&array, "peanut");
  char name = popDynArray(&array);
  ck_assert_msg(name == 't');
  char *arrayString = DynArrayToStr(&array);
  ck_assert_msg(strcmp(arrayString, "peanu") == 0, arrayString);
}
END_TEST

Suite *array_suite(void)
{
  Suite *s = suite_create("Array Init");

  TCase *tc_array_init_str = tcase_create("unit_test_array_init_string");
  tcase_add_test(tc_array_init_str, ut_array_init_str_works);
  suite_add_tcase(s, tc_array_init_str);
  TCase *tc_array_init_size = tcase_create("unit_test_array_init_size");
  tcase_add_test(tc_array_init_size, ut_array_init_size_works);
  suite_add_tcase(s, tc_array_init_str);
  TCase *tc_array_init_and_insert_char_works = tcase_create("unit_test_array_init_and_insert_char_works");
  tcase_add_test(tc_array_init_and_insert_char_works, ut_array_init_and_insert_char_works);
  suite_add_tcase(s, tc_array_init_and_insert_char_works);
  TCase *tc_array_init_and_add_string_works = tcase_create("unit_test_array_init_and_add_string_works");
  tcase_add_test(tc_array_init_and_add_string_works, ut_array_init_and_add_string_works);
  suite_add_tcase(s, tc_array_init_and_add_string_works);
  TCase *tc_array_init_and_remove_char_works = tcase_create("unit_test_array_init_and_remove_char_works");
  tcase_add_test(tc_array_init_and_remove_char_works, ut_array_init_and_remove_char_works);
  suite_add_tcase(s, tc_array_init_and_remove_char_works);
  TCase *tc_array_init_and_pop_works = tcase_create("unit_test_array_init_and_pop_works");
  tcase_add_test(tc_array_init_and_pop_works, ut_array_init_and_pop_works);
  suite_add_tcase(s, tc_array_init_and_pop_works);

  return s;
}

int main() {
  int number_failed;
  SRunner *sr = srunner_create(array_suite());
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

