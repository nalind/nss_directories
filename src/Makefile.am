moduleexecdir = @moduledir@
moduleexec_LTLIBRARIES = libnss_directories.la

EXTRA_libnss_directories_la_SOURCES = \
	generic.c
libnss_directories_la_SOURCES = \
	parsers.h \
	group.c \
	passwd.c \
	protocols.c \
	services.c \
	shadow.c

libnss_directories_la_LDFLAGS = \
	-version-info 2 -export-symbols-regex "_nss_directories.*"

install-exec-hook:
	mv $(DESTDIR)/$(moduleexecdir)/libnss_directories.so.2.0.0 \
	   $(DESTDIR)/$(moduleexecdir)/libnss_directories-@GLIBC_VERSION@.so
	$(RM) -f $(DESTDIR)/$(moduleexecdir)/libnss_directories.so*
	$(RM) -f $(DESTDIR)/$(moduleexecdir)/libnss_directories.a
	$(RM) -f $(DESTDIR)/$(moduleexecdir)/libnss_directories.la
