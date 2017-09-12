CXXFLAGS = -std=c++11
arithmetic: lib/Parser.o arithmetic.cpp
test: lib/Parser.o test.cpp
clean:
	rm -f arithmetic lib/*.o
