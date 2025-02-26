MAINPROG=listMajor
DIR=${PWD}
ASST=$(notdir ${DIR})
CC=gcc
CXX=g++
##
# Adjust settings for different compilers
#
ifeq ($(OS),Windows_NT)
#
# Flags for Windows compilers
ifeq ($(shell uname -o),Cygwin)
CPPFLAGS=-g -std=c++17 -MMD -pthread  -Wall
else
CPPFLAGS=-g -std=c++17 -MMD -pthread -D_GLIBCXX_DEBUG -Wall
endif
LFLAGS=
RM=del /q
EXE=.exe
TIMELIMIT=
else
#
# Flags for Linux & MacOS
CPPFLAGS=-g -std=c++17 -MMD -pthread -D_GLIBCXX_DEBUG -Wall
LFLAGS=
RM=/bin/rm -rf
EXE=
UNAME_S=$(shell uname -s)
ifeq ($(UNAME_S),Linux)
  TIMELIMIT=timeout 30s
else
  TIMELIMIT=
endif
endif
#
########################################################################
# Macro definitions for "standard" C and C++ compilations
#
CFLAGS=-g
TARGET=$(MAINPROG)$(EXE)
CPPS=$(wildcard *.cpp)
MAINCPPS=$(filter-out unittest.cpp test%.cpp, $(CPPS))
TESTCPPS=$(filter-out $(MAINPROG).cpp, $(CPPS))
 
.SECONDARY:

LINK=g++ $(CPPFLAGS)
#
########################################################################
#
#
#  In most cases, you should not change anything below this line.
#
#  The following is "boilerplate" to set up the standard compilation
#  commands:
#


MAINOBJS=$(MAINCPPS:%.cpp=%.o)
TESTOBJS=$(TESTCPPS:%.cpp=%.o)
DEPENDENCIES = $(CPPS:%.cpp=%.d)

# Macro definitions for systems tests
#
TESTFILES=$(wildcard Tests/*/*.in)
TESTCASES=$(dir $(TESTFILES))
TESTSOUT=$(sort $(TESTCASES:%=%/test.out))
TESTSDIFF=$(sort $(TESTCASES:%=%/test.diff))



%.d: %.cpp
	touch $@

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -o $@ -c $*.cpp

# 
# Targets:
# 

all: compile

compile: $(TARGET) unittest$(EXE) 

tests: unitTests systemTests

unitTests: ./unittest$(EXE)
	./unittest$(EXE)

systemTests: $(TARGET) $(TESTSDIFF)

Tests/%.out: Tests/%.yaml  $(TARGET)
	bash ./runTest.sh `basename $*` Tests .

$(TARGET): $(MAINOBJS)
	$(LINK) $(FLAGS) -o $(TARGET) $^ $(LFLAGS)

unittest$(EXE): $(TESTOBJS)
	$(LINK) $(FLAGS) -o $@ $^ $(LFLAGS)


clean: cleanTests
	-/bin/rm -rf *.d *.o $(TARGET) unittest$(EXE) docs 

cleanTests:
	-/bin/rm -f Tests/*/test.out Tests/*/test.diff 

documentation:
	-mkdir docs
	doxygen Doxyfile

%.out: $(TARGET)
	$(TIMELIMIT) ./$(TARGET) < $(dir $*)/test.in >  $@  2>&1

%/test.diff: %/test.out
	-diff -B $*test.out `ls $**.expected` | tee $@
	-@diff -q -B $*test.out `ls $**.expected` && echo !!! Passed $* || echo !!! Failed $*



make.dep: $(DEPENDENCIES)
	-cat $(DEPENDENCIES) > $@

include make.dep
