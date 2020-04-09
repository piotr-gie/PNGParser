__start__: a.out
	./a.out

a.out: main.o PNGParser.o
	g++ main.o PNGParser.o

main.o: main.cpp PNGParser.hpp
	g++ -c -Wall -pedantic main.cpp

PNGParser.o: PNGParser.hpp PNGParser.cpp
	g++ -c -Wall -pedantic PNGParser.cpp
