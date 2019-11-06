#include<iostream>
#pragma once

class BigInt {
	friend std::ostream& operator<<(std::ostream& stream, const BigInt& a);
	friend BigInt operator+(const BigInt& b, const BigInt& a);
	friend BigInt operator-(const BigInt& b, const BigInt& a);

	bool is_positive;
	char* memory;
	std::size_t size, maxsize;
	
public:
	static std::size_t reserve_size;
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
std::ostream& operator<<(std::ostream& stream, const BigInt& a);