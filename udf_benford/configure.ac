dnl AC_PREREQ([2.64])
AC_INIT([udf_benford], [1.0], [])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

AC_LANG([C])
AC_PROG_CC
AM_PROG_AR
LT_INIT

AM_CONFIG_HEADER([config.h:config.in])
AC_CONFIG_SRCDIR([src/udf_benford.c])

AC_CHECK_PROG(mysqlconfig, mysql_config, true)
if test "x${mysqlconfig}" != xtrue; then
    AC_MSG_ERROR([mysql_config not found in PATH])
fi

AC_ARG_WITH(
    [mysql],
    [AS_HELP_STRING([--with-mysql], [path to mysql])],
    [mysql_cflags="-I$withval"],
    [mysql_cflags="$(mysql_config --cflags)"])
mysql_ldflags="$(mysql_config --libs)"

CFLAGS="$CFLAGS $mysql_cflags"
LDFLAGS="$LDFLAGS $mysql_ldflags"

AC_CHECK_HEADERS(
    [stdlib.h string.h],
    [],
    [AC_MSG_ERROR([required system header not found])])

AC_CHECK_HEADERS(
    [mysql.h],
    [],
    [AC_MSG_ERROR([required header not found; install libmysqlclient-dev])])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
