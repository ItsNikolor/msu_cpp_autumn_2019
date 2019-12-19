all: test

test.o: test.cpp
	g++ -c -o test.o test.cpp

sort_file.o: sort_file.cpp
	g++ -c -o sort_file.o sort_file.cpp

test: test.o sort_file.o
	g++ -o test test.o sort_file.o -pthread

run: test
	./test
