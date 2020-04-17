all: test

main.o: main.cpp vector.h
	g++ -c -g -O2 main.cpp

out: main.o
	g++ -g -O2 main.o -o out
    
test: out
	./out


