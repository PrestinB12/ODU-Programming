DIR=${PWD}
ASST=$(notdir ${DIR})
MAINPROG=pdriver
CC=gcc
CXX=g++
##
# Adjust settings for different compilers
#
ifeq ($(OS),Windows_NT)
#
# Flags for Windows compilers
CPPFLAGS=-g -std=c++17 -MMD
LFLAGS=
RM=del /q
EXE=.exe
else
#
# Flags for Linux & MacOS
CPPFLAGS=-g -std=c++17 -MMD
LFLAGSx=
RM=/bin/rm -rf
EXE=
endif
#
########################################################################
# Macro definitions for "standard" C and C++ compilations
#
CPPFLAGS=-g -D$(DISTR)
CFLAGS=-g
TARGET=$(MAINPROG)$(EXE)
CPPS=pdriver.cpp permute.cpp
LINK=g++ $(CPPFLAGS)
#
CC=gcc
CXX=g++
#
#
#  In most cases, you should not change anything below this line.
#
#  The following is "boilerplate" to set up the standard compilation
#  commands:
#


OBJS=$(CPPS:%.cpp=%.o)
DEPENDENCIES = $(CPPS:%.cpp=%.d)



%.d: %.cpp
	touch $@

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -MMD -o $@ -c $*.cpp

# 
# Targets:
# 
all: $(TARGET)

$(TARGET): $(OBJS)
	$(LINK) $(FLAGS) -o $(TARGET) $(OBJS) $(LFLAGS)

clean:
	-/bin/rm -f *.d *.o $(TARGET)



make.dep: $(DEPENDENCIES)
	-cat $(DEPENDENCIES) > $@

include make.dep