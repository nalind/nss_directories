set -x
autoreconf
./configure --sysconfdir=/etc --with-moduledir=/lib/`gcc -print-multi-directory` $@
