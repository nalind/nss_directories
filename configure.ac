AC_INIT(README)
AM_INIT_AUTOMAKE(nss_directories,0.1)
AM_PROG_LIBTOOL

MYPREFIX=`eval echo $prefix`
if test "$MYPREFIX" = NONE ; then
	MYPREFIX="$ac_default_prefix"
	MYSYSCONFDIR=`eval echo $sysconfdir | sed "s|NONE|$MYPREFIX|g"`
else
	MYSYSCONFDIR=`eval echo $sysconfdir`
fi

AC_DEFINE_UNQUOTED(SYSCONFDIR,"$MYSYSCONFDIR",[Define to the top-level data directory.])

AC_ARG_WITH(moduledir,[  --with-moduledir=DIR    directory to install modules in (default /lib)],[moduledir="$withval"])
if ! test -n "$moduledir"
then
	moduledir=/lib
fi
AC_SUBST(moduledir)

AC_CHECK_LIB(nss_files,_nss_files_parse_pwent)
AC_CHECK_LIB(nss_files,_nss_files_parse_grent)
AC_CHECK_LIB(nss_files,_nss_files_parse_spent)
AC_CHECK_LIB(nss_files,_nss_files_parse_servent)
AC_CHECK_LIB(nss_files,_nss_files_parse_protoent)

nss_files=`ls -1 "$moduledir"/libnss_files-*.so | head -1`
GLIBC_VERSION=`basename "$nss_files" .so | cut -f2 -d-`
AC_SUBST(GLIBC_VERSION)

AM_CONFIG_HEADER(config.h)
AC_OUTPUT(Makefile src/Makefile)

AC_MSG_RESULT([Reading data from sysconfdir = "$MYSYSCONFDIR".])
AC_MSG_RESULT([Installing modules to "$moduledir".])
