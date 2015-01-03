AC_INIT([react_render], [0.0.1],
        [https://github.com/tildedave/isomorphic-react-without-node/issues])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
LT_INIT

AC_PROG_CC
m4_include([m4/ac_pkg_swig.m4])

AC_DISABLE_STATIC
AC_PROG_LIBTOOL
AC_PROG_SWIG(3.0.0)
AM_PATH_PYTHON([2.5],, [:])
SWIG_PYTHON

AC_ARG_VAR(DUKTAPE, Path to duktape src directory (required))

AC_CHECK_HEADERS([$DUKTAPE/duktape.h], break, AC_MSG_ERROR([Couldn't find duktape.h!]))
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile python/Makefile])
AC_OUTPUT
