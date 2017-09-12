CXXFLAGS = -std=c++11
arithmetic: lib/Parser.o lib/ShuntingYard.o arithmetic.cpp
test: lib/Parser.o lib/ShuntingYard.o test.cpp
clean:
	rm -f arithmetic lib/*.o
