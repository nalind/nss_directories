set -x
libtoolize -f -c
aclocal
autoheader
automake -a
autoconf
./configure --sysconfdir=/etc --with-moduledir=/lib/`gcc -print-multi-directory` $@
