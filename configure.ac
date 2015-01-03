AC_INIT([react_render], [0.0.1],
        [https://github.com/tildedave/isomorphic-react-without-node/issues])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
LT_INIT

AC_PROG_CC
AC_CONFIG_MACRO_DIR([m4])

AC_DISABLE_STATIC
AC_PROG_LIBTOOL
AC_PROG_SWIG(3.0.0)
AM_PATH_PYTHON([2.5],, [:])
SWIG_PYTHON

AX_JNI_INCLUDE_DIR

JAVA_CPPFLAGS=""
for JNI_INCLUDE_DIR in $JNI_INCLUDE_DIRS
do
        JAVA_CPPFLAGS="$JAVA_CPPFLAGS -I$JNI_INCLUDE_DIR"
done
AC_SUBST(JAVA_CPPFLAGS)

AC_ARG_VAR(DUKTAPE, Path to duktape src directory (required))

AC_CHECK_HEADERS([$DUKTAPE/duktape.h], break, AC_MSG_ERROR([Couldn't find duktape.h!]))
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile python/Makefile java/Makefile])
AC_OUTPUT
