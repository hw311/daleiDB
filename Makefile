.PHONY : clean all tests debug doc

BINDIR   := bin
BUILDDIR := build
SRCDIR   := src
TESTDIR  := tests
DOCDIR   := doc
AUXDIR   := $(BINDIR) $(BUILDDIR)

TARGET  :=
OBJECTS :=

MKDIR := mkdir
RM    := rm -rf

CC  ?= g++
CXX ?= $(CC)
DOC ?= doxygen

DOCCONFIG ?= .doxyconfig

CPPFLAGS := -std=c++17 -Wall

all : $(OBJECTS)

debug : CPPFLAGS += -O0 -D DEBUG -g3
debug : $(OBJECTS)

doc :
	$(DOC) $(DOCCONFIG)

$(AUXDIR) :
	$(MKDIR) $@

clean :
	$(RM) $(AUXDIR)
