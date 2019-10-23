#include<iostream>
#include"LinearAllocator.h"

int main() {
	LinearAllocator a;//Стандартный размер 100 байт
	char* s;
	std::cout << (void*)(s = a.alloc(0)) <<'\n';
	std::cout << (void*)(s = a.alloc(30)) << '\n';
	std::cout << (void*)(s = a.alloc(1)) << '\n';
	std::cout << (void*)(s = a.alloc(69)) << '\n';
	std::cout << (void*)(s = a.alloc(1)) << '\n';
	std::cout << '\n';
	a.reset();

	std::cout << (void*)(s = a.alloc(101)) << '\n';
	std::cout << (void*)(s = a.alloc(1)) << '\n';
	std::cout << (void*)(s = a.alloc(1)) << '\n';
	std::cout << (void*)(s = a.alloc(20)) << '\n';
	std::cout << "\n\n";

	LinearAllocator b(0);
	std::cout << (void*)(s = b.alloc(1)) << '\n';
	std::cout << "\n\n";

	LinearAllocator c(5);
	std::cout << (void*)(s = c.alloc(1)) << '\n';
	std::cout << (void*)(s = c.alloc(1)) << '\n';
	std::cout << (void*)(s = c.alloc(1)) << '\n';
	std::cout << (void*)(s = c.alloc(1)) << '\n';
	std::cout << (void*)(s = c.alloc(1)) << '\n';
	std::cout << (void*)(s = c.alloc(1)) << '\n';
	std::cout << '\n';
	c.reset();

	std::cout << (void*)(s = c.alloc(5)) << '\n';
	std::cout << (void*)(s = c.alloc(1)) << '\n';
	std::cout << '\n';
	c.reset();

	std::cout << (void*)(s = c.alloc(6)) << '\n';
	std::cout << (void*)(s = c.alloc(1)) << '\n';
	std::cout << (void*)(s = c.alloc(1)) << '\n';
	std::cout << (void*)(s = c.alloc(1)) << '\n';
	std::cout << (void*)(s = c.alloc(1)) << '\n';
	std::cout << (void*)(s = c.alloc(1)) << '\n';
	std::cout << (void*)(s = c.alloc(1)) << '\n';

}
