.PHONY : clean all run

PROJECT_ROOT := ..

BINDIR   := bin
BUILDDIR := build
SRCDIR   := src
AUXDIR   := $(BINDIR) $(BUILDDIR)

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

PROJ_SOURCES := $(wildcard $(PROJECT_ROOT)/$(SRCDIR)/*.cpp)
PROJ_OBJECTS :=\
$(PROJ_SOURCES:$(PROJECT_ROOT)/$(SRCDIR)/%.cpp=$(PROJECT_ROOT)/$(BUILDDIR)/%.o)

TARGET := $(BINDIR)/run_unit_tests

CPPFLAGS += -I../utils -I ../src

all : $(TARGET) $(OBJECTS)

run : $(TARGET)
	./$(TARGET)

$(AUXDIR) :
	$(MKDIR) $@

$(OBJECTS) : $(BUILDDIR)/%.o : $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) -c -o $@ $< $(CPPFLAGS)

$(TARGET) : $(OBJECTS) $(PROJ_OBJECTS) | $(BINDIR)
	$(CXX) -o $@ $^ $(CPPFLAGS)

clean :
	$(RM) $(AUXDIR)
