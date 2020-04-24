all: test

main.o: main.cpp threadpool.h
	g++ -c -g -O2 main.cpp

out: main.o
	g++ -g -O2 main.o -lpthread -o out
    
test: out
	./out
