#include<iostream>
#include"BigInt.h"
#include<limits.h>
#include<cassert>
using namespace std;

int main() {
	BigInt* fib_array = new BigInt[332];
	fib_array[0] = fib_array[1] = 1;
	int i = 2;

	for (BigInt n = 2; n < 332; n = n + 1) {
		fib_array[i] = fib_array[i - 1] + fib_array[i - 2];
		i++;
	}
	cout <<' '<< fib_array[331] << endl;// Это 332 число в ряду фиббоначи

	BigInt* fib_array_neg = new BigInt[332];
	fib_array_neg[0] = fib_array_neg[1] = -1;
	i = 2;

	for (BigInt n = 2; n < 332; n = n + 1) {
		fib_array_neg[i] = fib_array_neg[i - 1] + fib_array_neg[i - 2];
		i++;
	}
	cout << fib_array_neg[331] << endl;// Это 332 число в ряду фиббоначи, со знаком минус

	BigInt* fib_array2 = new BigInt[332];
	fib_array2[331] = fib_array[331];
	fib_array2[330] = fib_array[330];
	i = 329;
	for (BigInt n = 329; n >=0; n = n - 1) {// Получаю числа фиббоначи через последние два посредством отнимания
		fib_array2[i] = fib_array2[i + 2] - fib_array2[i + 1];
		i--;
	}

	for (int j = 0; j < 332; j++) assert(fib_array[j] == fib_array2[j]);
	for (int j = 2; j < 332; j++) assert(fib_array[j] > fib_array[j - 1]);
	for (int j = 0; j < 332; j++) assert(fib_array[j] == -fib_array_neg[j]);
	for (int j = 0; j < 332; j++) assert(fib_array[j]+fib_array_neg[j] == 0);
	for (int j = 0; j < 332; j++) assert(fib_array_neg[j] + fib_array[j] == 0);
	for (int j = 1; j < 332; j++) assert(fib_array[j-1] > fib_array_neg[j]);
	for (int j = 0; j < 332; j++) assert(fib_array_neg[j] - fib_array_neg[j] == 0);
	for (int j = 0; j < 332; j++) assert(fib_array[j] - fib_array[j] == 0);
	for (int j = 0; j < 332; j++) assert(BigInt(j)+fib_array_neg[j] + fib_array[j]- BigInt(j) == 0);

	BigInt* fib_array_moved = new BigInt[332];
	std::copy(fib_array, fib_array + 332, fib_array_moved);

	for (int j = 0; j < 332; j++) fib_array_moved[j] = std::move(fib_array[j]);

	for (int j = 0; j < 332; j++) assert(fib_array_moved[j] == fib_array2[j]);
	for (int j = 0; j < 332; j++) assert(fib_array[j]+5 == 5);

	BigInt a = 0, b, c(0), d = 1;

	assert(a == b && b == c && c != d && c < d);
	assert(c == d - d && d == d + a && d == b + d);

	BigInt t = 1000000000;
	for (int i = 0; i < 100000-1; i++) t = t + 1000000000;//t=1e14

	cout << ' '<<t - 1 << endl;
	cout << 1 - t << endl;
	cout << 1 - t - (t - 1) << endl;

	assert(BigInt(123456789) - BigInt(123456666) == 123);
	assert(BigInt(123456666) - BigInt(123456789) == -123);
	system("pause");
}