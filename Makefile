# mcl - Mud Client for Unix
# Makefile.in - this file is processed by configure to create the Makefile
# created by Rodrigo Parra Novo <rodarvus@conectiva.com.br> - 19990907
# first based on the Makefile of mcl version 0.5something

# Common autoconf flags
CC=gcc
CXX=g++
CFLAGS=-O2
CPPFLAGS=
CXXFLAGS=-O2
DEFS=-DPACKAGE_NAME=\"\" -DPACKAGE_TARNAME=\"\" -DPACKAGE_VERSION=\"\" -DPACKAGE_STRING=\"\" -DPACKAGE_BUGREPORT=\"\" 
EXE=mcl
INSTALL=/usr/bin/install -c
LDFLAGS=-s -rdynamic
LIBS=
prefix=/usr/local
INSTALL_ROOT=
COMPILED_BY=alex@alex-VirtualBox
MODULES=perl python

# Common programs
LN_S=ln -s
RM=/bin/rm
FIND=/usr/bin/find
XARGS=/usr/bin/xargs
CTAGS=/usr/bin/ctags
ECHO=/bin/echo

# Compile with perl libraries?
# Shut up the compiler about something caused by perl 5.6
PERL=/usr/bin/perl
PERL_CPPFLAGS= -I/usr/lib/x86_64-linux-gnu/perl/5.24/CORE  -Wno-unused
PERL_LDFLAGS=-Wl,-E  -fstack-protector-strong -L/usr/local/lib  -L/usr/lib/x86_64-linux-gnu/ -lperl -ldl -lm -lpthread -lc -lcrypt

# Compile with python libraries?
PYTHON=/usr/bin/python
PYTHON_CPPFLAGS=-I/usr/include/python2.7
PYTHON_LDFLAGS=-L/usr/lib/python2.7/config -lpython2.7

# Extra libraries
LIBDL=-ldl
LIBEFENCE=
LIBM=-lm
LIBNCURSES=-lncurses
LIBPTHREAD=-lpthread
LIBZ=-lz

# Extra compiler flags
HAVE_FLAG_NO_RTTI=-fno-rtti
HAVE_FLAG_NO_EXCEPTIONS=-fno-exceptions
LOCAL_CFLAGS=
LOCAL_CPPFLAGS=-Ih
LOCAL_CXXFLAGS=
LOCAL_LDFLAGS=
LOCAL_LIBS=

# Common flags
MCL_CFLAGS=$(CFLAGS) $(CPPFLAGS) $(DEFS) $(LOCAL_CFLAGS) $(LOCAL_CPPFLAGS)
MCL_CXXFLAGS=$(CXXFLAGS) $(CPPFLAGS) $(DEFS) $(HAVE_FLAG_NO_RTTI) \
	$(HAVE_FLAG_NO_EXCEPTIONS) $(LOCAL_CXXFLAGS) $(LOCAL_CPPFLAGS)
MCL_LDFLAGS=$(LDFLAGS) $(LOCAL_LDFLAGS)
MCL_LIBS=$(LIBS) $(LOCAL_LIBS) $(LIBDL) $(LIBEFENCE) $(LIBM) $(LIBNCURSES) $(LIBZ)

# Source files
SRC_FILES := $(wildcard *.cc)

# Object files
OBJ_DIR=o
OBJ_FILES := $(patsubst %.cc,$(OBJ_DIR)/%.o,$(SRC_FILES)) $(OBJ_DIR)/mccpDecompress.o
DEPS := $(patsubst %, $(OBJ_DIR)/plugins/%.so, $(MODULES))

# Include files
INC_FILES := $(wildcard h/*.h)

.PHONY: all distclean clean tidy install

all: $(EXE) $(DEPS)

distclean: clean
	$(RM) -f config.* Makefile VERSION mcl.spec h/config.h

clean: tidy 
	$(RM) -f $(OBJ_FILES) $(EXE) o/plugins/*.so o/plugins/*.o

tidy:
	$(RM) -f *~ *orig *bak *rej doc/*~ samples/*~
	$(FIND) samples -name "*~" -print | $(XARGS) $(RM) -f

.depend:
	$(CXX) -MM -Ih $(SRC_FILES) > .depend
	$(PERL) -i -p -e 's/([^.]+)\.o/o\/\1.o/g' .depend

tags:	$(SRC_FILES) $(INC_FILES)
	$(CTAGS) $(SRC_FILES) $(INC_FILES)

# Link with $(CC) to avoid the c++ libs to be linked
$(EXE): $(OBJ_FILES)
	$(CXX) $(MCL_LDFLAGS) -o $(EXE) $(OBJ_FILES) $(MCL_LIBS)

$(OBJ_DIR)/%.o: %.cc
	$(CXX) -c $(MCL_CXXFLAGS) $< -o $@

$(OBJ_DIR)/mccpDecompress.o: mccpDecompress.c
	$(CC) -c $(MCL_CFLAGS) $< -o $@

o/plugins/perl.so: o/plugins/PerlEmbeddedInterpreter.o
	$(CC) $(LDFLAGS) -shared $< -o $@ $(PERL_LDFLAGS) $(LIBPTHREAD)

o/plugins/PerlEmbeddedInterpreter.o: plugins/PerlEmbeddedInterpreter.cc
	$(CC) -c -fpic $(MCL_CFLAGS) $(PERL_CPPFLAGS) $< -o $@

o/plugins/python.so: o/plugins/PythonEmbeddedInterpreter.o
	$(CC) $(LDFLAGS) -shared $< -o $@ $(PYTHON_LDFLAGS) $(LIBPTHREAD)

o/plugins/PythonEmbeddedInterpreter.o: plugins/PythonEmbeddedInterpreter.cc
	$(CC) -c -fpic $(MCL_CFLAGS) $(PYTHON_CPPFLAGS) $< -o $@

install: $(EXE)
	$(INSTALL) -d $(INSTALL_ROOT)$(prefix)/{bin,lib/mcl/{auto,contrib,plugins,sys}}
	$(INSTALL) $(EXE) $(INSTALL_ROOT)$(prefix)/bin
	$(INSTALL) o/plugins/*.so $(INSTALL_ROOT)$(prefix)/lib/mcl/plugins || : # There may be no plugins to install
	$(INSTALL) samples/auto/*.* $(INSTALL_ROOT)$(prefix)/lib/mcl/auto/ # The *.* is desired, not a typo
	$(INSTALL) samples/contrib/*.* $(INSTALL_ROOT)$(prefix)/lib/mcl/contrib/
	$(INSTALL) samples/sys/*.* $(INSTALL_ROOT)$(prefix)/lib/mcl/sys/


include admin/Makefile
include .depend
