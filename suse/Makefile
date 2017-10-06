include ../common.mak

all: read_values

LDLIBS += -lqc

dasdview: read_values.o

install: all
	$(INSTALL) -d -m 755 $(DESTDIR)$(BINDIR) $(DESTDIR)$(MANDIR)/man8
	$(INSTALL) -g $(GROUP) -o $(OWNER) -m 755 read_values $(DESTDIR)$(BINDIR)
	$(INSTALL) -g $(GROUP) -o $(OWNER) -m 644 read_values.8 \
		$(DESTDIR)$(MANDIR)/man8

clean:
	rm -f *.o *~ read_values core

.PHONY: all install clean
