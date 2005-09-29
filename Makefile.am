SUBDIRS = src
EXTRA_DIST = ChangeLog COPYING README nss_directories.spec
DISTCHECK_CONFIGURE_FLAGS = --with-moduledir=$$dc_install_base/modules

NAME = nss_directories
VERSION=@VERSION@
CVSTAG = $(shell echo $(NAME)-$(VERSION) | sed -e s,\\.,_,g)

tag:
	cvs tag -c $(CVSTAG)

force-tag:
	cvs tag -cF $(CVSTAG)

archive:
	$(RM) -fr /tmp/$(NAME)-$(VERSION)
	cd /tmp ; cvs -d $(shell cat $(top_srcdir)/CVS/Root) export -r $(CVSTAG) -d $(NAME)-$(VERSION) $(NAME)
	cd /tmp/$(NAME)-$(VERSION) ; ./autogen.sh ; make distcheck
	mv -v /tmp/$(NAME)-$(VERSION)/$(NAME)-*.*.tar.* $(top_srcdir)/
	$(RM) -fr /tmp/$(NAME)-$(VERSION)

srpm: archive
	rpmbuild -ts $(NAME)-$(VERSION).tar.gz
