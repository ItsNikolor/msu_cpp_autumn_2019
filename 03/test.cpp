#include"Matrix.h"
#include <stdexcept>
#include <cassert>
#include<iostream>

int main() {
	const size_t rows = 5;
	const size_t cols = 3;

	Matrix m(rows, cols);

	assert(m.getRows() == 5);
	assert(m.getColumns() == 3);

	try {
		m[1][2] = 5;
		std::cout << m[1][2] << '\n';
	}
	catch (std::out_of_range) {
		std::cout << "Out of range\n";
	}
	catch (...) {
		std::cout << "Some error\n";
	}

	try {
		double x = m[4][1];
		std::cout << x << '\n';
	}
	catch (std::out_of_range) {
		std::cout << "Out of range\n";
	}
	catch (...) {
		std::cout << "Some error\n";
	}
	try {
		double x = m[5][1];
		std::cout << x << '\n';
	}
	catch (std::out_of_range) {
		std::cout << "Out of range\n";
	}
	catch (...) {
		std::cout << "Some error\n";
	}

	for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) m[i][j] = 25;
	Matrix m1(rows, cols);
	for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) m1[i][j] = 5;
	m1 *= m[0][0];// *25
	m *= 5;
	assert(m1 == m);
	m1[rows - 1][cols - 1] = 43;
	assert(m1 != m);
	Matrix m2(1, 1);
	assert(m != m2);

	try {
		double x = m[2][1];
		std::cout << x << '\n';
	}
	catch (std::out_of_range) {
		std::cout << "Out of range\n";
	}
	catch (...) {
		std::cout << "Some error\n";
	}
	Matrix m3(0, 5), m4(5, 0);
}
