all: test

main.o: main.cpp threadsort.h
	g++ -c -g -O2 main.cpp

threadsort.o: threadsort.cpp threadsort.h
	g++ -c -g -O2 threadsort.cpp

out: main.o threadsort.o
	g++ -g -O2 main.o threadsort.o -lpthread -o out
    
test: out
	./out
