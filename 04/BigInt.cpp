#include "BigInt.h"
#include<iostream>
#include<algorithm>

using namespace std;
size_t BigInt::reserve_size = 10;
BigInt::BigInt(int a):size(0),is_positive(a>=0),maxsize(0){
	if (a < 0) a = -a;
	int tmp = a;

	while (tmp != 0) {
		maxsize++;
		tmp /= 10;
	}

	memory = new char[maxsize];
	while (a != 0) {
		memory[size++] = (a % 10);
		a /= 10;
	}
}

BigInt::BigInt(const BigInt& copyed):memory(new char[copyed.maxsize]),is_positive(copyed.is_positive),maxsize(copyed.maxsize),size(copyed.size){
	copy(copyed.memory, copyed.memory + copyed.size, memory);
}

BigInt::BigInt(BigInt&& moved):memory(moved.memory),size(moved.size),is_positive(moved.is_positive),maxsize(moved.maxsize){
	moved.memory = nullptr;
	moved.maxsize = 0;
	moved.size = 0;
}

BigInt& BigInt::operator=(const BigInt& copyed){
	if(this==&copyed) return *this;
	auto tmp = new char[copyed.maxsize];
	delete[]memory;

	memory = tmp;
	size = copyed.size;
	copy(copyed.memory, copyed.memory + copyed.size, memory);
	is_positive = copyed.is_positive;
	maxsize = copyed.maxsize;

	return *this;
}

BigInt& BigInt::operator=(BigInt&& moved){
	if (this == &moved) return *this;
	delete[]memory;

	memory = moved.memory;
	size = moved.size;
	maxsize = moved.maxsize;
	is_positive = moved.is_positive;

	moved.memory = nullptr;
	moved.size = 0;
	moved.maxsize = 0;

	return *this;
}

BigInt::~BigInt(){
	delete[] memory;
}

BigInt BigInt::operator-() const {
	BigInt a(*this);
	a.is_positive = !is_positive;
	return a;
}

bool BigInt::operator>(const BigInt& a) const{

	if (is_positive != a.is_positive) return is_positive > a.is_positive;

	if (is_positive) {
		if (size != a.size) return size > a.size;
		else {
			for (int i = size - 1; i >= 0; i--)
				if (memory[i] > a.memory[i]) return true;
				else if (memory[i] < a.memory[i]) return false;
			return false;
		}
	}
	else {
		if (size != a.size) return size < a.size;
		else {
			for (int i = size - 1; i >= 0; i--)
				if (memory[i] > a.memory[i]) return false;
				else if (memory[i] < a.memory[i]) return true;
			return false;
		}
	}
}

bool BigInt::operator>=(const BigInt& a) const{
	return !(*this < a);
}

bool BigInt::operator==(const BigInt& a) const{
	if (is_positive != a.is_positive) return false;
	if (size != a.size) return false;
	for (size_t i = 0; i < size; i++) if (memory[i] != a.memory[i]) return false;
	return true;
}

bool BigInt::operator!=(const BigInt& a) const{
	return !(*this == a);
}

bool BigInt::operator<(const BigInt& a) const{
	return a > * this;
}

bool BigInt::operator<=(const BigInt& a) const{
	return !(*this > a);
}


BigInt operator+(const BigInt &b, const BigInt& a)
{
	bool add = 0;
	BigInt ans;
	delete[] ans.memory;
	ans.memory = new char[max(b.maxsize, a.maxsize)];

	if ((b.is_positive && a.is_positive) || (!b.is_positive && !a.is_positive)) {
		ans.is_positive = b.is_positive;

		for (size_t i = 0; i < min(b.size, a.size); i++) {
			ans.memory[i] = (b.memory[i] + a.memory[i] + add) % 10;
			add = (b.memory[i] + a.memory[i] + add) > 9;
		}

		char* greater_int = (b.size > a.size) ? b.memory : a.memory;
		for (size_t i = min(b.size, a.size); i < max(b.size, a.size); i++) {
			ans.memory[i] = (greater_int[i] + add) % 10;
			add = (greater_int[i] + add) > 9;
		}

		if (add && max(b.size, a.size) == b.maxsize) {// Нужно выделить больше памяти
			auto tmp = new char[b.maxsize + BigInt::reserve_size];

			copy(ans.memory, ans.memory + b.maxsize, tmp);
			tmp[b.maxsize] = add;

			delete[]ans.memory;
			ans.memory = tmp;
			ans.size = b.maxsize + 1;
			ans.maxsize = b.maxsize + BigInt::reserve_size;
		}
		else {
			if (add) ans.memory[max(b.size, a.size)] = 1;
			ans.size = (add) ? max(b.size, a.size) + 1 : max(b.size, a.size);
			ans.maxsize = max(b.maxsize, a.maxsize);
		}
	}
	else {
		BigInt& neg = const_cast<BigInt&>((b.is_positive) ? a : b);// Снимаю константность 
		neg.is_positive = !neg.is_positive;// Меняю объект
		const BigInt* greater, * less;

		if (b > a) {// Здесь я сравниваю абсолютные значения a и b, не хочется писать отдельную функцию для этого
			neg.is_positive = !neg.is_positive;//Возвращаю всё на место
			greater = &b, less = &a;
			ans.is_positive = b.is_positive;
		}
		else {
			neg.is_positive = !neg.is_positive;//Возвращаю всё на место
			greater = &a, less = &b;
			ans.is_positive = a.is_positive;
		}
		//К этому моменту я опять работаю с константыми объектами, при этом ничего изменено не было,
		//никакая ошибка на пути возникнуть не могла

		for (size_t i = 0; i < less->size; i++) {
			char tmp = greater->memory[i] - less->memory[i] - add;
			add = tmp < 0;

			ans.memory[i] = (tmp >= 0) ? tmp : 10 + tmp;
		}
		for (size_t i = less->size; i < greater->size; i++) {
			char tmp = greater->memory[i] - add;
			add = tmp < 0;

			ans.memory[i] = (tmp >= 0) ? tmp : 10 + tmp;
		}

		ans.size = greater->size;
		ans.maxsize = greater->maxsize;

		while (ans.size > 0 && ans.memory[ans.size - 1] == 0) ans.size--;
		if (ans.size == 0) ans.is_positive = true;
	}
	return ans;
}

BigInt operator-(const BigInt& b, const BigInt& a){
	if (&b == &a) return BigInt();

	BigInt newa;// Я хочу выполнить b+(-a), но не хочу создавать копию a
				// newa=-a, но без копирования
	delete[]newa.memory;
	newa.memory = a.memory;
	newa.is_positive = !a.is_positive;
	newa.size = a.size;
	newa.maxsize = a.maxsize;

	auto tmp = b + newa;
	newa.memory = nullptr;

	return tmp;
}

ostream& operator<<(ostream& stream, const BigInt& a){
	if (a.size==0) return stream << '0';
	if (!a.is_positive) stream << '-';
	for (int i = a.size - 1; i >= 0; i--) stream << char(a.memory[i]+'0');
	return stream;
}
