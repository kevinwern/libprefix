#ifndef ERROR_H
#define ERROR_H

typedef enum LIBPREFIX_ERROR_STATE {
  NO_ERROR,		// Default state if no error occurs.
  KEY_NOT_FOUND,	// Key not found in hash table.
  INCORRECT_ARR_TYPE,	// No way to perform operation on type of DynArray.
  ARR_NOT_INIT,		// DynArray not initialized.
  INVALID_INDEX,	// Index outside of DynArray.
  INSUFFICIENT_TOTAL,	// Total assigned members too small for operation.
  INVALID_SIZE		// Size of array is invalid.
} LIBPREFIX_ERROR_STATE;

extern LIBPREFIX_ERROR_STATE LIBPREFIX_ERROR;

// Get last error that was set.
LIBPREFIX_ERROR_STATE libprefix_error_last();

// Get human-readable string for error state.
char *libprefix_strerror(LIBPREFIX_ERROR_STATE state);

// Set error state.
void libprefix_set_error(LIBPREFIX_ERROR_STATE state);
#endif
