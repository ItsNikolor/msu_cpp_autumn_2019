#pragma once
#include<iostream>
#include<sstream>
#include"Error.h"

class Deserializer {
	std::istream* in_;
public:
	explicit Deserializer(std::istream& in) :in_(&in) {}

	template <class T>
	Error load(T& object)
	{
		return object.serialize(*this);
	}

	template <class... ArgsT>
	Error operator()(ArgsT&&... args)
	{
		return process(args...);
	}

private:
	template<class T, class... Args>
	Error process(T& val, Args&& ... args) {
		if (process_one(val) == Error::CorruptedArchive) return Error::CorruptedArchive;
		else return process(std::forward<Args>(args)...);
	}

	template<class T>
	Error process(T& val) {
		return process_one(val);
	}

	template<class T>
	Error process_one(T& val) {
		return Error::CorruptedArchive;
	}

	template<>
	Error process_one<bool>(bool& val) {
		std::string tmp;
		*in_ >> tmp;

		if (in_->eof()) {
			in_->clear();
			return Error::CorruptedArchive;
		}

		if (tmp[0] == 't') val = true;
		else if (tmp[0] == 'f') val = false;
		else return Error::CorruptedArchive;

		return Error::NoError;
	}

	template<>
	Error process_one<uint64_t>(uint64_t& val) {
		std::string tmp;
		*in_ >> tmp;

		if (in_->eof()) {
			in_->clear();
			return Error::CorruptedArchive;
		}

		if (tmp[0] == 't' || tmp[0] == 'f') return Error::CorruptedArchive;
		else {
			std::stringstream s;
			s << tmp;
			s >> val;
		}
		return Error::NoError;
	}

};