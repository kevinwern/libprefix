#include "liberrors.h"

LIBPREFIX_ERROR libprefix_error_last()
{
  return LIBPREFIX_ERROR;
}

char *libprefix_strerror(LIBPREFIX_ERROR_STATE state);
{
  switch (state)
  {
    case NO_ERRORS:
      return "No errors";
    case KEY_NOT_FOUND:
      return "Key not found";
    case INCORRECT_ARR_TYPE:
      return "Array not the right type for operation";
    default:
      return "Unknown or incorrect code";
  }
}
void libprefix_set_error(LIBPREFIX_ERROR_STATE state);
{
  return LIBPREFIX_ERROR;
}
