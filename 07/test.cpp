#include<iostream>
#include<cassert>
#include"vector.h"

using namespace std;


int main() {
	Vector<int> a(3,666);
	for (int i = 0; i < 10; i++) a.push_back(i);
	for (auto i : a) cout << i << ' ';
	cout << "\n=====================================\n";
	for (auto i = a.rbegin(); i != a.rend(); ++i) cout << *i << ' ';
	cout << "\n\n";
	assert(a.size() == 13);
	
	for (int i = 0; i < a.size(); i++) cout << a[i] << ' ';
	cout << "\n\n";
	auto it = a.begin();
	*it = 888;
	a[1] = 777;
	for (int i = 0; i < a.size(); i++) cout << a[i] << ' ';
	cout << "\n\n";


	for (int i = 0; i < 5; i++) a.pop_back();
	for (auto i : a) cout << i << ' ';
	cout << "\n=====================================\n";
	for (auto i = a.rbegin(); i != a.rend(); ++i) cout << *i << ' ';
	cout << "\n\n";
	assert(a.size() == 8);

	a.resize(10,8);
	for (auto i : a) cout << i << ' ';
	cout << "\n=====================================\n";
	for (auto i = a.rbegin(); i != a.rend(); ++i) cout << *i << ' ';
	cout << "\n\n";
	assert(a.size() == 10);

	a.resize(2, 3);
	for (auto i : a) cout << i << ' ';
	cout << "\n=====================================\n";
	for (auto i = a.rbegin(); i != a.rend(); ++i) cout << *i << ' ';
	cout << "\n\n";
	assert(a.size() == 2);

	a.clear();
	for (auto i : a) cout << i << ' ';
	cout << "\n=====================================\n";
	for (auto i = a.rbegin(); i != a.rend(); ++i) cout << *i << ' ';
	cout << "\n\n";
	assert(a.size() == 0);

	Vector<string> b;
	assert(b.size() == 0);
	assert(b.empty() == 1);
	b.push_back("string");
	assert(b.empty() == 0);
	assert(b.size() == 1);

	b.reserve(100);
	assert(b.size() == 1);
	b.reserve(0);
	assert(b.size() == 1);

	const Vector<double> c(10, 42.0);
	auto t = c.begin();
	double tmp = *t;
	//*t = tmp;
	for (auto i : c) cout << i << ' ';
	cout << "\n=====================================\n";
	for (auto i = c.rbegin(); i != c.rend(); ++i) cout << *i << ' ';
	cout << "\n\n";
	
	for (int i = 0; i < c.size(); i++) cout << c[i] << ' ';
	cout << "\n\n";
	
	assert(c.size() == 10);
	assert(c.empty() == 0);
}