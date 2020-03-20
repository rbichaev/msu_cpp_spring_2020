all: test

main.o: main.cpp matrix.h
	g++ -c -g -O2 main.cpp

matrix.o: matrix.cpp matrix.h
	g++ -c -g -O2 matrix.cpp

out: main.o matrix.o
	g++ -g -O2 main.o matrix.o -o out

test: out
	./out