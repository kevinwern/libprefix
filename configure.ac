#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(libprefix, 1.0, kevin.m.wern@gmail.com)
AC_CONFIG_SRCDIR([src/graph.h])
AC_CONFIG_HEADERS([config.h])
m4_pattern_allow([AM_PROG_AR])
AM_PROG_AR
AM_INIT_AUTOMAKE([-Wall foreign])
m4_pattern_allow([AM_PATH_CHECK])
AM_PATH_CHECK([0.9.0],[])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_PROG_RANLIB
AM_PROG_CC_C_O

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
LT_INIT

# Checks for library functions.
AC_FUNC_MALLOC

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 test/Makefile])
AC_OUTPUT

