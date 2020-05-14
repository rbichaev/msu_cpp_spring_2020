all: test

main.o: main.cpp threadsum.h
	g++ -c -g -O2 main.cpp

threadsum.o: threadsum.cpp threadsum.h
	g++ -c -g -O2 threadsum.cpp

out: main.o threadsum.o
	g++ -g -O2 main.o threadsum.o -lpthread -o out
    
test: out
	./out