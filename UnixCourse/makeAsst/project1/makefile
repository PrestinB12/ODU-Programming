all: computeSqrt

computeSqrt: computeSqrt.o sqrt.o
	g++ -o computeSqrt  computeSqrt.o sqrt.o

computeSqrt.o: computeSqrt.cpp sqrt.h
	g++ -c computeSqrt.cpp
 
sqrt.o: sqrt.cpp sqrt.h
	g++ -c sqrt.cpp
