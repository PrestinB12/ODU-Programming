all: playChomp

playChomp: cookie.o mainProg.o
	g++ -o playChomp cookie.o mainProg.o

cookie.o: cookie.cpp cookie.h 
	g++ -c cookie.cpp cookie.h

mainProg.o: mainProg.cpp cookie.h
	g++ -c mainProg.cpp cookie.h

cookie.cpp:  xx01 
	cp xx01 cookie.cpp


cookie.h:  xx00
	cp xx00 cookie.h

xx00: chomp.adt
	csplit chomp.adt "/Split Here/"

xx01: chomp.adt
	csplit chomp.adt "/Split Here/"

