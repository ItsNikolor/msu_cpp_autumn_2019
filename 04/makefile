all: test
test.o: test.cpp
	g++ -c -o test.o test.cpp
BigInt.o: BigInt.cpp
	g++ -c -o BigInt.o BigInt.cpp
test: BigInt.o test.o
	g++ -o test BigInt.o test.o
run: test
	./test
valgrind: test
	valgrind -v ./test
