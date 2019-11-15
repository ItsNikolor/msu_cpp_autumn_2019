#pragma once
#include<iostream>
#include<sstream>
#include"Error.h"

class Deserializer {
	std::istream &in_;
public:
	explicit Deserializer(std::istream& in) :in_(in) {}

	template <class T>
	Error load(T& object)
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
	Error process(T&& val, Args&& ... args) {
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
		std::string tmp;
		in_ >> tmp;

		if (in_.eof()) {
			in_.clear();
			return Error::CorruptedArchive;
		}

		if (tmp == "true") val = true;
		else if (tmp == "false") val = false;
		else return Error::CorruptedArchive;

		return Error::NoError;
	}

	Error process_one(uint64_t& val) {
		std::string tmp;
		in_ >> tmp;
		if (tmp[0] == '-') return Error::CorruptedArchive;
		tmp = '0' + tmp;

		if (in_.eof()) {
			in_.clear();
			return Error::CorruptedArchive;
		}

		if (tmp == "true" || tmp == "false") return Error::CorruptedArchive;
		else {
			size_t pos = 0;
			int number = stoull(tmp, &pos);
			if (pos != tmp.size()) return  Error::CorruptedArchive;
			else val = number;

			return Error::NoError;
		}
		
	}

};