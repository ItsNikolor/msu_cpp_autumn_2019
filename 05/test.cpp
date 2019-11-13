#include<iostream>
#include"serializer.h"
#include"Deserializer.h"
#include"Error.h"
#include<sstream>
#include<cassert>
using namespace std;

struct Data
{
	uint64_t a;
	bool b;
	uint64_t c;

	template <class Serializer>
	Error serialize(Serializer& serializer)
	{
		return serializer(a, b, c);
	}
};

struct Data1
{
	uint64_t a;
	uint64_t b;
	uint64_t c;

	template <class Serializer>
	Error serialize(Serializer& serializer)
	{
		return serializer(a, b, c);
	}
};

struct Data2
{
	bool a;
	bool b;
	bool c;

	template <class Serializer>
	Error serialize(Serializer& serializer)
	{
		return serializer(a, b, c);
	}
};

struct single_bool{
	bool a;
	template <class Serializer>
	Error serialize(Serializer& serializer)
	{
		return serializer(a);
	}
};

struct single_int {
	uint64_t a;
	template <class Serializer>
	Error serialize(Serializer& serializer)
	{
		return serializer(a);
	}
};

int main() {
	Data x{ 1, true, 2 };

	std::stringstream stream;

	Serializer serializer(stream);
	serializer.save(x);

	Data y{ 0, false, 0 };

	Deserializer deserializer(stream);
	Error err = deserializer.load(y);

	assert(err == Error::NoError);

	assert(x.a == y.a);
	assert(x.b == y.b);
	assert(x.c == y.c);


	Data1 x1{ 1,2,3 }, y1{ 4,5,6 };
	Data2 x2{ true, true, false }, y2{ false,false,true };

	serializer.save(x1);
	serializer.save(x2);

	err = deserializer.load(y1);
	assert(err == Error::NoError);
	assert(x1.a == y1.a);
	assert(x1.b == y1.b);
	assert(x1.c == y1.c);


	err = deserializer.load(y2);
	assert(err == Error::NoError);
	assert(x2.a == y2.a);
	assert(x2.b == y2.b);
	assert(x2.c == y2.c);

	single_bool b{ true };
	single_int i{ 42 };

	serializer.save(i);
	serializer.save(b);
	serializer.save(b);

	err = deserializer.load(y);
	assert(err == Error::CorruptedArchive);

	err = deserializer.load(b);
	assert(err == Error::CorruptedArchive);

	serializer.save(i);
	err = deserializer.load(i);
	assert(err == Error::NoError);


	serializer.save(b);
	serializer.save(b);
	serializer.save(b);

	serializer.save(i);
	serializer.save(i);
	serializer.save(b);

	err = deserializer.load(y2);
	assert(err == Error::NoError);

	err = deserializer.load(i);
	assert(err == Error::NoError);

	err = deserializer.load(y);
	assert(err == Error::CorruptedArchive);

	return 0;
}