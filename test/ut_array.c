// ut_array.c
// unit test for DynArray Library

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "../src/array.h"
//#define TEST_SIZE 5
//#define TEST_STRING "peanuts"

START_TEST (ut_array){
  // Does character hash work properly?

  DynArray array;

  initDynArrayStr(&array, "peanuts");
  ck_assert_msg(array.size == 8);
  printf ("%d\n", array.size);
  printDynArray(&array);


}
END_TEST

Suite *array_suite (void)
{
  Suite *s = suite_create ("Array");

  /* Core test case */
  TCase *tc_array = tcase_create ("unit_test_array");
  tcase_add_test (tc_array, ut_array);
  suite_add_tcase (s, tc_array);

  return s;
}

int main() {
  int number_failed;
  Suite *s = array_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all (sr, CK_NORMAL);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

