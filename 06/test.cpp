#include<iostream>
#include<string>
#include"format.h"
#include<cassert>

using namespace std;

int main()
{
	auto text = format("{1}+{1} = {0}", 2, "one");
	assert(text == "one+one = 2");
	
	string a0 = "zero", a1 = "one", a2 = "two";
	string* a3 = &a2;
	bool a4 = true, a5 = false;
	const string a6 = "siiiiiiix";
	int a7 = 1234567890;
	double a8 = 3.1415926535;
	char a9 = 'c';

	text = format("{0}  {1}  {2}  {3}  {4}  {5}  {6}  {7}  {8}  {9}  {10}  {11} some text",
			a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, 10101010, "string_with_space    slovo");

	stringstream stream;
	stream << &a2;
	string tmp_addres;
	stream >> tmp_addres;
	string test = "zero  one  two  "+tmp_addres+"  1  0  siiiiiiix  1234567890  3.14159  c  10101010  string_with_space some text";
	assert(text == test);

	text = format("some text");
	assert(text == "some text");
	
	text = format("some text", a0, a1, a2, a3, a4, a5, a6, 7, a8, a9);
	assert(text == "some text");

	text = format("{0}{1}", "{2}{2}", "{1}");
	assert(text == "{2}{2}{1}");


	try {
		text = format("{0}");
	}
	catch (std::runtime_error a) {
		cout << a.what() << endl;
	}

	try {
		text = format("{-1}",1);
	}
	catch (std::runtime_error a) {
		cout << a.what() << endl;
	}

	try {
		text = format("{ab}", 1);
	}
	catch (std::runtime_error a) {
		cout << a.what() << endl;
	}

	try {
		text = format("{0}{", 1,2);
	}
	catch (std::runtime_error a) {
		cout << a.what() << endl;
	}

	try {
		text = format("{2}", 0, 1);
	}
	catch (std::runtime_error a) {
		cout << a.what() << endl;
	}

	try {
		text = format("{2000000000000000000000000000000000000000000000000000}", 0, 1);
	}
	catch (std::runtime_error a) {
		cout << a.what() << endl;
	}

	try {
		text = format("{0", 0, 1);
	}
	catch (std::runtime_error a) {
		cout << a.what() << endl;
	}

	try {
		text = format("}0", 0, 1);
	}
	catch (std::runtime_error a) {
		cout << a.what() << endl;
	}


	return 0;
}