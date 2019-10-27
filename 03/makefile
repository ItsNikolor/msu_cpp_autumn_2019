all: test
test.o: test.cpp
	g++ -c -o test.o test.cpp
Matrix.o: Matrix.cpp
	g++ -c -o Matrix.o Matrix.cpp
test: Matrix.o test.o
	g++ -o test Matrix.o test.o
run: test
	./test
valgrind: test
	valgrind -v ./test
