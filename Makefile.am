SUBDIRS = src
EXTRA_DIST = ChangeLog COPYING README nss_directories.spec
DISTCHECK_CONFIGURE_FLAGS = --with-moduledir=$$dc_install_base/modules

NAME = nss_directories
VERSION=@VERSION@
RELEASE=@RELEASE@
CVSTAG = $(shell echo $(NAME)-$(VERSION) | sed -e s,\\.,_,g -e s,-,_,g)

tag:
	cvs tag -c $(CVSTAG)

force-tag:
	cvs tag -cF $(CVSTAG)

distdir = $(NAME)-$(VERSION)-$(RELEASE)
archive:
	$(RM) -fr /tmp/$(NAME)-$(VERSION)
	cd /tmp ; cvs -d $(shell cat $(top_srcdir)/CVS/Root) export -r $(CVSTAG) -d $(NAME)-$(VERSION)-$(RELEASE) $(NAME)
	cd /tmp/$(NAME)-$(VERSION)-$(RELEASE) ; ./autogen.sh ; make distcheck
	mv -v /tmp/$(NAME)-$(VERSION)-$(RELEASE)/$(NAME)-*.*.tar.* $(top_srcdir)/
	$(RM) -fr /tmp/$(NAME)-$(VERSION)-$(RELEASE)

srpm: archive
	rpmbuild -ts $(NAME)-$(VERSION)-$(RELEASE).tar.gz
