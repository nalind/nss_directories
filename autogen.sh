set -x
libtoolize -f -c
aclocal
automake -a
autoheader
autoconf
./configure --sysconfdir=/etc --with-moduledir=/lib/`gcc -print-multi-directory` $@
