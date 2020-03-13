all: test

main.o: main.cpp parser.h
	g++ -c -g -O2 main.cpp

parser.o: parser.cpp parser.h
	g++ -c -g -O2 parser.cpp

out: main.o parser.o
	g++ -g -O2 main.o parser.o -o out

test: out
	./out