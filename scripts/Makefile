include ../common.mak

SCRIPTS	= dbginfo.sh zfcpdbf scsi_logging_level cputype mkdump
MAN_PAGES = dbginfo.sh.1 zfcpdbf.1 cputype.1
MAN8_PAGES = mkdump.8

all:

install:
	$(INSTALL) -d -m 755 $(DESTDIR)$(BINDIR) $(DESTDIR)$(MANDIR)/man1 $(DESTDIR)$(MANDIR)/man8

	@for i in $(SCRIPTS); \
	do \
		cat $$i | \
		sed -e 's+%S390_TOOLS_VERSION%+$(S390_TOOLS_RELEASE)+' \
		>$(DESTDIR)$(BINDIR)/$$i; \
		chown $(OWNER):$(GROUP) $(DESTDIR)$(BINDIR)/$$i; \
		chmod 755 $(DESTDIR)$(BINDIR)/$$i; \
	done

	sed -e 's+%S390_TOOLS_VERSION%+$(S390_TOOLS_RELEASE)+' cpictl > \
		$(DESTDIR)$(TOOLS_LIBDIR)/cpictl
	chown $(OWNER):$(GROUP) $(DESTDIR)$(TOOLS_LIBDIR)/cpictl
	chmod 775 $(DESTDIR)$(TOOLS_LIBDIR)/cpictl

	@for i in $(MAN_PAGES); \
	do \
		$(INSTALL) -g $(GROUP) -o $(OWNER) -m 644 $$i \
		$(DESTDIR)$(MANDIR)/man1; \
	done

	@for i in $(MAN8_PAGES); \
	do \
		$(INSTALL) -g $(GROUP) -o $(OWNER) -m 644 $$i \
		$(DESTDIR)$(MANDIR)/man8; \
	done
clean:

.PHONY: all install clean
