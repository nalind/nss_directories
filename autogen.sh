set -x
autoreconf -i
./configure --sysconfdir=/etc --with-moduledir=/lib/`gcc -print-multi-directory` $@
