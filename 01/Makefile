all: test

alloc.o: alloc.cpp alloc.h
	g++ -c -g -O2 alloc.cpp 

main.o: main.cpp alloc.h
	g++ -c -g -O2 main.cpp

out: main.o alloc.o
	g++ -g -O2 main.o alloc.o -o out

test: out
	./out