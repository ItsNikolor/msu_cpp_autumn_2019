#pragma once
#include<iostream>
#include<string>
#include"Error.h"

class Serializer
{
	static constexpr char Separator = ' ';
	std::ostream& out_;
public:
	
	explicit Serializer(std::ostream &out) :out_(out) {}

	template <class T>
	Error save(T& object)
	{
		return object.serialize(*this);
	}

	template <class... ArgsT>
	Error operator()(ArgsT&&... args)
	{
		return process(std::forward<ArgsT>(args)...);
	}

private:
	template<class T, class... Args>
	Error process(T&& val, Args&&... args) {
		if (process_one(val) == Error::CorruptedArchive) return Error::CorruptedArchive;
		else return process(std::forward<Args>(args)...);
	}

	template<class T>
	Error process(T&& val) {
		return process_one(val);
	}

	template<class T>
	Error process_one(T&& val) {
		return Error::CorruptedArchive;
	}

	Error process_one(bool& val) {
		if (val) out_ << "t" << Separator;
		else out_ << "f" << Separator;
		return Error::NoError;
	}

	Error process_one(uint64_t& val) {
		out_ << val << Separator;
		return Error::NoError;
	}

};
