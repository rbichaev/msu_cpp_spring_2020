all: test

main.o: main.cpp bigint.h
	g++ -c -g -O2 main.cpp

matrix.o: bigint.cpp bigint.h
	g++ -c -g -O2 bigint.cpp

out: main.o bigint.o
	g++ -g -O2 main.o bigint.o -o out

test: out
	./out
