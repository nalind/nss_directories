lib_LTLIBRARIES = libnss_directories.la

if MAINTAINER_MODE
AM_CFLAGS = -Wall -Wextra
endif

EXTRA_libnss_directories_la_SOURCES = \
	files-parse.c \
	generic.c \
	parsers.h

EXTRA_programs = test

libnss_directories_la_SOURCES = \
	glibc-parse.c \
	group.c \
	passwd.c \
	protocols.c \
	services.c \
	shadow.c

libnss_directories_la_LDFLAGS = \
	-version-info 2 \
	-export-symbols-regex "_nss_directories_[sge].*"

install-exec-hook:
	$(RM) -f $(DESTDIR)/$(moduleexecdir)/libnss_directories.so*
	$(RM) -f $(DESTDIR)/$(moduleexecdir)/libnss_directories.a
	$(RM) -f $(DESTDIR)/$(moduleexecdir)/libnss_directories.la
