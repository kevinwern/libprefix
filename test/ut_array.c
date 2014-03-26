// ut_array.c
// unit test for DynArray Library

#include <check.h>
#include <stdio.h>
#include "../src/array.h"
#define TEST_SIZE 5
#define TEST_STRING 'peanuts'

START_TEST (ut_array){
  // Does character hash work properly?

  DynArray array;

  initDynArray(&array, TEST_SIZE);
  ck_assert_msg(array.size = 8);

  initDynArrayString

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


int main() {
  return 0;
}
