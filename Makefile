.PHONY : clean all tests run_tests debug doc

BINDIR   := bin
BUILDDIR := build
SRCDIR   := src
TESTDIR  := tests
DOCDIR   := doc
AUXDIR   := $(BINDIR) $(BUILDDIR)

TARGET=\

OBJECTS=\
$(BUILDDIR)/paged_file_manager.o \

MKDIR := mkdir -p
RM    := rm -rf

CC  ?= g++
CXX ?= $(CC)
DOC ?= doxygen

DOCCONFIG ?= .doxyconfig

CPPFLAGS ?= -std=c++17 -Wall

export MKDIR
export RM
export CC
export CXX
export CPPFLAGS

all : $(OBJECTS)

debug : CPPFLAGS += -O0 -D DEBUG -g3
debug : $(OBJECTS)

tests : CPPFLAGS += -fprofile-arcs -ftest-coverage
tests : $(OBJECTS)
	$(MAKE) -C $(TESTDIR)

run_tests : tests
	$(MAKE) -C $(TESTDIR) run

doc :
	$(DOC) $(DOCCONFIG)

$(AUXDIR) :
	$(MKDIR) $@

$(BUILDDIR)/paged_file_manager.o : $(SRCDIR)/paged_file_manager.cpp
$(BUILDDIR)/paged_file_manager.o : $(SRCDIR)/common.hpp
$(BUILDDIR)/paged_file_manager.o : $(SRCDIR)/paged_file_manager.hpp
$(BUILDDIR)/paged_file_manager.o : $(SRCDIR)/file_manager_exception.hpp
$(BUILDDIR)/paged_file_manager.o : | $(BUILDDIR)
$(BUILDDIR)/paged_file_manager.o :
	$(CXX) -c -o $@ $< $(CPPFLAGS)

clean :
	$(RM) $(AUXDIR)
	$(MAKE) -C $(TESTDIR) clean
