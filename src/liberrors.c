#include "liberrors.h"

LIBPREFIX_ERROR_STATE LIBPREFIX_ERROR = NO_ERROR;

LIBPREFIX_ERROR_STATE libprefix_error_last()
{
  return LIBPREFIX_ERROR;
}

char *libprefix_strerror(LIBPREFIX_ERROR_STATE state)
{
  switch (state)
  {
    case NO_ERROR:
      return "No errors";
    case KEY_NOT_FOUND:
      return "Key not found";
    case INCORRECT_ARR_TYPE:
      return "Array not the right type for operation";
    default:
      return "Unknown or incorrect code";
  }
}

void libprefix_set_error(LIBPREFIX_ERROR_STATE state)
{
  LIBPREFIX_ERROR = state;
}
