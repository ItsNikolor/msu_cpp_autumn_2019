#include<iostream>
#pragma once
using namespace std;

class BigInt {
public:
	friend ostream& operator<<(ostream& stream, const BigInt& a);
	friend BigInt operator+(const BigInt& b, const BigInt& a);
	friend BigInt operator-(const BigInt& b, const BigInt& a);
	mutable bool is_positive;
	char* memory;
	size_t size, maxsize;
public:
	BigInt(int a = 0);
	BigInt(const BigInt& copyed);
	BigInt(BigInt&& moved);
	BigInt& operator=(const BigInt& copyed);
	BigInt& operator=(BigInt&& moved);
	~BigInt();


	BigInt operator-() const;
	bool operator>(const BigInt& a) const;
	bool operator==(const BigInt& a) const;
	bool operator!=(const BigInt& a) const;
	bool operator<(const BigInt& a) const;
	bool operator<=(const BigInt& a) const;
	bool operator>=(const BigInt& a) const;
};
BigInt operator+(const BigInt &b, const BigInt& a);
BigInt operator-(const BigInt& b, const BigInt& a);
ostream& operator<<(ostream& stream, const BigInt& a);