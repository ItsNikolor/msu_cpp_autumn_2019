#include<iostream>
#include<fstream>
#include<cassert>
#include"sort_file.h"

using namespace std;

int main() {
	const size_t memory_size = 4194304;
	size_t TrueCount = 3*memory_size / sizeof(uint64_t) + 100;
	ofstream ofile;
	uint64_t t;
	ifstream file;

	ofile.open("binary.dat", ios::binary);
	if (!ofile.is_open()) {
		cout << "Cant open\n";
		return 0;
	}

	for (uint64_t i = TrueCount; i > 0; i--) ofile.write((char*)&i, sizeof(uint64_t));
	ofile.close();
	
	try {
		sort_file("binary.dat", "out.dat");

		file.open("out.dat", ios::binary);

		for (uint64_t i = 1; i <= TrueCount; ++i) {
			file.read((char*)&t, sizeof(uint64_t));
			assert(t == i);
		}
		file.close();
	}
	catch (exception err) {
		cout << err.what();
	}
	catch (...) {
		cout << "Something wrong\n";
	}


	TrueCount = 1 * memory_size / sizeof(uint64_t) + 3;
	ofile.open("binary.dat", ios::binary);
	if (!ofile.is_open()) {
		cout << "Cant open\n";
		return 0;
	}

	for (uint64_t i = 0; i < TrueCount; i++) ofile.write((char*)&i, sizeof(uint64_t));
	ofile.close();
	
	try {
		sort_file("binary.dat", "out.dat");

		file.open("out.dat", ios::binary);
		for (uint64_t i = 0; i < TrueCount; ++i) {
			file.read((char*)&t, sizeof(uint64_t));
			assert(t == i);
		}
		file.close();
	}
	catch (exception err) {
		cout << err.what();
	}
	catch(...) {
		cout << "Something wrong\n";
	}
}