#
# makefile for testlist program
#
########################################################################
# Macro definitions for "standard" C and C++ compilations
#
#  Define special compilation flags for C++ compilation. These may change when
#  we're done testing and debugging.
CPPFLAGS=-g
#
# 
#  Define special linkage flags.  Usually, these are used to include
#  special libraries of code, e.g., -lm to add the library of mathematical
#  routines such as sqrt, sin, cos, etc.
LFLAGS=-lm

# Compilation command pattern: how to produce .o files from a .cpp file
.cpp.o: ; g++ $(CPPFLAGS) -MMD -c $*.cpp

CC=gcc
CPP=g++




#
# The first target is the default: what to build if you just say "make"
#
#
#  Rebuild testlist whenever either testlist.o or namelist.o have changed.
#  The 2nd line gives the command used to create testlist from those .o 
#  files.
testlist: testlist.o namelist.o
	g++ $(CPPFLAGS) -o testlist testlist.o namelist.o $(LFLAGS)

#
# Other files to build
#

#
# Build testlist.o from testlist.cpp 
# Because we don't give a rule here for how to do this, the default rule
# for producing .o files from .cpp files, defined above, will be used.
#
# The dependencies here indicate that testlist.o needs to be rebuilt 
# whenever we have made a change to either testlist.cpp or namelist.h
#
testlist.o: testlist.cpp namelist.h

#
# Build namelist.o from namelist.cpp 
# Again, we use the default rule for producing .o files from .cpp files.
#
# The dependencies here indicate that namelist.o needs to be rebuilt 
# whenever we have made a change to either namelist.cpp or namelist.h
#
namelist.o: namelist.cpp namelist.h



#
# A dummy target: "make clean" will remove all files that "make" produces.
#
clean:
	-/bin/rm testlist *.o

