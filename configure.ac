#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(tagal, 0.2a, monnand@gmail.com)
AC_CONFIG_SRCDIR([libtagal/error.c])
AM_CONFIG_HEADER([include/config.h])
AM_INIT_AUTOMAKE(tagal, 0.2a)

# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h assert.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([memmove memset strchr strdup strerror strrchr strstr])

AC_CONFIG_SUBDIRS([sqlite])
AC_CONFIG_SUBDIRS([gtk-tagal])
AC_CONFIG_SUBDIRS([for-nautilus-actions])

AC_CONFIG_FILES([Makefile
                 libtagal/Makefile])
AC_OUTPUT
