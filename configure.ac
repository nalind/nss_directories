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

nss_files=`ls -1 "$moduledir"/libnss_files-*.so | head -1`
GLIBC_VERSION=`basename "$nss_files" .so | cut -f2 -d-`
if test -z "$GLIBC_VERSION"
then
	GLIBC_VERSION=$PACKAGE_VERSION
fi
AC_SUBST(GLIBC_VERSION)

if test x$GCC = xyes ; then
	CFLAGS="${CFLAGS} -std=c99"
	CFLAGS="${CFLAGS} -D_GNU_SOURCE"
	CFLAGS="${CFLAGS} -Wall"
	CFLAGS="${CFLAGS} -Waggregate-return"
	CFLAGS="${CFLAGS} -Wcast-align"
	CFLAGS="${CFLAGS} -Wimplicit"
	CFLAGS="${CFLAGS} -Wmissing-declarations"
	CFLAGS="${CFLAGS} -Wmissing-prototypes"
	CFLAGS="${CFLAGS} -Wpointer-arith"
	CFLAGS="${CFLAGS} -Wstrict-prototypes"
	CFLAGS="${CFLAGS} -Wuninitialized"
fi

AM_CONFIG_HEADER(config.h)
AC_OUTPUT(Makefile src/Makefile)

AC_MSG_RESULT([Reading data from sysconfdir = "$MYSYSCONFDIR".])
AC_MSG_RESULT([Installing modules to "$moduledir".])
