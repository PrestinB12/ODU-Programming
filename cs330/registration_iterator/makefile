MAINPROG=register
CPPS= register.cpp Course.cpp Student.cpp Schedule.cpp
TEST_CPPS= Course.cpp Student.cpp Schedule.cpp TestSchedule.cpp
DIR=${PWD}
ASST=$(notdir ${DIR})
ifneq (,$(findstring MinGW,$(PATH)))
DISTR=MinGW
EXE=.exe
LFLAGS=
else
DISTR=Unix
EXE=
LFLAGS=-fsanitize=leak,address -fuse-ld=gold -Wall -Wpedantic
endif
#
########################################################################
# Macro definitions for "standard" C and C++ compilations
#
CPPFLAGS=-g -std=c++11 -D$(DISTR)
CFLAGS=-g
TARGET=$(MAINPROG)$(EXE)
TEST_TARGET=testSchedule$(EXE)
LINK=g++ $(CPPFLAGS)
#
CC=gcc
CPP=g++
#
#
#  In most cases, you should not change anything below this line.
#
#  The following is "boilerplate" to set up the standard compilation
#  commands:
#


OBJS=$(CPPS:%.cpp=%.o)
DEPENDENCIES = $(CPPS:%.cpp=%.d)

TEST_OBJS=$(TEST_CPPS:%.cpp=%.o)


%.d: %.cpp
	touch $@

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -MMD -o $@ -c $*.cpp

#
# Targets:
#
all: $(TARGET) tests


win: $(OBJS)
	$(LINK) $(FLAGS) -o $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(LINK) $(FLAGS) -o $(TARGET) $(OBJS) $(LFLAGS)

tests: $(TEST_OBJS)
	$(LINK) $(FLAGS) -o $(TEST_TARGET) $(TEST_OBJS)


clean:
	-/bin/rm -f *.d *.o $(TARGET) $(TEST_TARGET)



make.dep: $(DEPENDENCIES)
	-cat $(DEPENDENCIES) > $@

include make.dep
