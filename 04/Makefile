all: test

main.o: main.cpp ser_des.h
	g++ -c -g -O2 main.cpp

ser_des.o: ser_des.cpp ser_des.h
	g++ -c -g -O2 ser_des.cpp

out: main.o ser_des.o
	g++ -g -O2 main.o ser_des.o -o out
    
test: out
	./out
