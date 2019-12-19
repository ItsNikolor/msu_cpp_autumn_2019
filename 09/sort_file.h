#pragma once

#include<string>
#include<exception>

namespace sort_file_name {
	class my_except : public std::exception {
	public:
		my_except(std::string const& message) : msg_(message) { }
		virtual char const* what() const noexcept { return msg_.c_str(); }

	private:
		std::string msg_;
	};
}

void sort_file(const char* in_path, const char* output_path, const char* tmp_path = "tmp.dat", size_t num_threads = 2);
