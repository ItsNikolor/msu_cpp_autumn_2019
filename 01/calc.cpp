#include<iostream>
#include<limits.h>
using namespace std;

enum state { Fail, Suc, KeepGoing };
enum error {Fine,Division_by_zero,Overflow,Bad_input};

int to_int(const char* str, int& pos, error &e, const int int_max_deg) {
	int ans = 0, sign = 1;

	while (str[pos] == ' ') pos++;

	if (str[pos] == '-') {
		sign = -1;
		pos++;
	}
	if (str[pos] < '0' || str[pos]>'9') {
		e = Bad_input;
		return 0;
	}

	while (str[pos] == '0') pos++;

	int deg = 0;
	while (str[pos] >= '0' && str[pos] <= '9') {
		deg++;
		if (deg == int_max_deg) {// Вся эта ветка нужна, чтобы проверить данное число на переполнение
			if ((str[pos + 1] >= '0' && str[pos + 1] <= '9') || INT_MAX / 10 < abs(ans)) {
				e = Overflow;
				return 0;
			}
			if (INT_MAX / 10 == abs(ans)) {
				if ((sign == 1 && str[pos] - '0' > INT_MAX % 10)
					|| (sign == -1 && str[pos] - '0' > -(INT_MIN % 10))) {
					e = Overflow;
					return 0;
				}
			}
		}
		ans = ans * 10 + sign*(str[pos++] - '0');
	}
	return ans;
}
state op(int& pos, int& sum, int& multiplier, const char* str, error &e, const int int_max_deg) {
	if (e != Fine) return Fail;
	while (str[pos] == ' ') pos++;
	if (str[pos] == '\0') return Suc;

	int plus = (str[pos] == '+') ? 1 : 0, minus = (str[pos] == '-') ? 1 : 0\
		, mul = (str[pos] == '*') ? 1 : 0, del = (str[pos] == '/') ? 1 : 0;

	if ((plus + minus + mul + del) == 0) {
		e = Bad_input;
		return Fail;
	}
	pos++;
	int tmp = to_int(str, pos, e, int_max_deg);
	sum = sum + (plus + minus) * multiplier;
	if (del) {
		if (tmp) multiplier = multiplier / tmp;
		else {
			e = Division_by_zero;
			return Fail;
		}
	}
	else multiplier = plus * tmp - minus * tmp + mul * multiplier * tmp;
	return KeepGoing;
}
void err(error e) {
	switch (e) {
	case Division_by_zero:
		cout << "Division by zero";
		return;
	case Bad_input:
		cout << "Bad input";
		return;
	case Overflow:
		cout << "Overflow";
	}
}

int f(const char* str, error &e) {
	e = Fine;
	int tmp = INT_MAX, max_int_deg = 0;
	while (tmp != 0) {// Скольки значное int_max(а также int_min) число
		max_int_deg++;
		tmp /= 10;
	}
	int sum = 0, pos = 0, multiplier = to_int(str, pos, e, max_int_deg);
	state st = KeepGoing;
	while (1) {
		switch (st)
		{
		case Fail:
			return -1;
		case Suc:
			cout << sum + multiplier;
			return 0;
		case KeepGoing:
			st = op(pos, sum, multiplier, str, e, max_int_deg);
		}
	}
}

int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "Wrong number of arguments";
		return -1;
	}
	else {
		error e = Fine;
		int ans = f(argv[1], e);
		err(e);
		return ans;
	}
}
