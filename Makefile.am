SUBDIRS = src
EXTRA_DIST = README nss_directories.spec
DISTCHECK_CONFIGURE_FLAGS = --with-moduledir=$$dc_install_base/modules

NAME = nss_directories
VERSION = $(shell rpm -q --specfile --qf '%{version}' $(top_srcdir)/$(NAME).spec)
CVSTAG = $(shell echo $(NAME)-$(VERSION) | sed -e s,\\.,_,g -e s,-,_,g)

tag:
	cvs tag -c $(CVSTAG)

force-tag:
	cvs tag -cF $(CVSTAG)

archive:
	$(RM) -fr /tmp/$(NAME)-$(VERSION)
	cd /tmp ; cvs -d $(shell cat $(top_srcdir)/CVS/Root) export -r $(CVSTAG) -d $(NAME)-$(VERSION) $(NAME)
	cd /tmp/$(NAME)-$(VERSION) ; ./autogen.sh ; make distcheck
	mv /tmp/$(NAME)-$(VERSION)/$(NAME)-$(VERSION).tar.* $(top_srcdir)/
	$(RM) -fr /tmp/$(NAME)-$(VERSION)
	
