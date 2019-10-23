all: test
test.o: test.cpp
	g++ -c -o test.o test.cpp
LinearAllocator.o: LinearAllocator.cpp
	g++ -c -o LinearAllocator.o LinearAllocator.cpp
test: LinearAllocator.o test.o
	g++ -o tes LinearAllocator.o test.o
run: test
	./test
valgrind: test
	valgrind -v ./test
