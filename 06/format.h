#include<string>
#include<iostream>
#include<sstream>
#include<stdexcept>
#include<limits>
#include<vector>

int check_int(const std::string& s,size_t &pos) {
	long long num = 0;
	for (; pos < s.size(); pos++) {
		if (s[pos] > '9' || s[pos] < '0') break;
		num = num * 10 + s[pos] - '0';
		if (num > INT_MAX) break;
	}
	if (s[pos] != '}') return -1;
	else return num;
}

bool can_stream(...) {
	return false;
}

template<class T>
bool can_stream(std::string &s, T &&t, typename decltype(std::cout << t)* = nullptr) {
	std::stringstream tmp_stream;
	tmp_stream << t;
	tmp_stream >> s;
	return true;
}

void parse_args(std::vector<std::string>& args) {
	return;
}

template<class T,class... ArgsT>
void parse_args(std::vector<std::string>& args, T &&a, ArgsT&& ...arg) {
	args.push_back("");
	if (can_stream(args.back(),a)) {
		parse_args(args, std::forward<ArgsT>(arg)...);
	}
	else throw (std::runtime_error("Cant output to stream"));
}




template<class... ArgsT>
std::string format(const std::string& s, ArgsT&&... arg) {
	std::vector<std::string> args;
	parse_args(args, std::forward<ArgsT>(arg)...);
	std::string ans = "";
	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] == '{') {
			if (i == s.size() - 1) throw(std::runtime_error("Wrong balance with {"));
			int num = check_int(s, ++i);
			if (num == -1) throw(std::runtime_error("Wrong number in brackets"));
			if (num >= args.size()) throw(std::runtime_error("Too few arguments"));
			ans += args[num];
		}
		else if (s[i] == '}') throw(std::runtime_error("Wrong balance with }"));
		else ans += s[i];
	}
	return ans;
}
