SRC=.

include ../Common.mk

all: libcodegen echoprint-codegen

libcodegen: $(MODULES_LIB)
ifeq ($(UNAME),Darwin)
	libtool -dynamic -flat_namespace -install_name libcodegen.$(VERSION).dylib -lSystem -compatibility_version $(VERSION_COMPAT) \
		-macosx_version_min 10.6 -current_version $(VERSION) -o libcodegen.$(VERSION).dylib -undefined suppress \
	    $(MODULES_LIB) -framework vecLib -framework Accelerate
else
	$(CXX) -shared -fPIC -Wl,-soname,$(SONAME) -o $(LIBNAME).$(VERSION) $(MODULES_LIB) -lz -lfftw3
endif

echoprint-codegen: $(MODULES) main.o
	$(CXX) $(MODULES) $(LDFLAGS) main.o -o ../echoprint-codegen

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.cxx %.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o ../echoprint-codegen
	rm -f libcodegen.so*
ifeq ($(UNAME),Darwin)
	rm -f *.dylib
endif

PREFIX ?= /usr/local
DESTDIR ?= $(PREFIX)
BINDIR ?= /bin
LIBDIR ?= /lib
INCLUDEDIR ?= /include

install: all
	install -d $(DESTDIR)$(BINDIR)
	install ../echoprint-codegen $(DESTDIR)$(BINDIR)
	install -d $(DESTDIR)$(INCLUDEDIR)/echoprint
	install -pm 644 Codegen.h $(DESTDIR)$(INCLUDEDIR)/echoprint/
	install -d $(DESTDIR)$(LIBDIR)
ifeq ($(UNAME),Darwin)
	install -m 755 libcodegen.$(VERSION).dylib $(DESTDIR)$(LIBDIR)
	ln -fs $(DESTDIR)$(LIBDIR)/libcodegen.$(VERSION) $(DESTDIR)$(LIBDIR)/libcodegen.$(VERSION_MAJ).dylib
	ln -fs $(DESTDIR)$(LIBDIR)/libcodegen.$(VERSION_MAJ).dylib $(DESTDIR)$(LIBDIR)/libcodegen.dylib
else
	install -m 755 $(LIBNAME).$(VERSION) $(DESTDIR)$(LIBDIR)
	ln -fs $(DESTDIR)$(LIBDIR)/$(LIBNAME).$(VERSION) $(DESTDIR)$(LIBDIR)/$(SONAME)
	ln -fs $(DESTDIR)$(LIBDIR)/$(SONAME) $(DESTDIR)$(LIBDIR)/$(LIBNAME)
endif

.PHONY: clean all libcodegen echoprint-codegen install
