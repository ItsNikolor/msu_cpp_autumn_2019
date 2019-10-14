#include<iostream>
using namespace std;
int max_int = (unsigned int)(~0) >> 1;
unsigned int min_int = ~max_int;
int int_deg = 0;
enum state { Fail, Suc, KeepGoing };
enum error {Fine,Division_by_zero,Overflow,Bad_input};
int to_int(const char* argv, int& i,error &e) {
	int ans = 0, znak = 1;
	while (argv[i] == ' ') i++;
	if (argv[i] == '-') {
		znak = -1;
		i++;
	}
	if (argv[i] < '0' || argv[i]>'9') {
		e=Bad_input;
		return 0;
	}
	while (argv[i] == '0') i++;
	int deg = 0;
	while (argv[i] >= '0' && argv[i] <= '9') {
		deg++;
		if (deg == int_deg) {// Вся эта ветка нужна, чтобы проверить данное число на переполнение
			if ((argv[i + 1] >= '0' && argv[i + 1] <= '9') || max_int / 10 < ans) {
				e=Overflow;
				return 0;
			}
			if (max_int / 10 == ans) {
				if (znak == 1) {
					if ((argv[i] - '0') > max_int % 10) {
						e=Overflow;
						return 0;
					}
				}
				else {
					if ((argv[i] - '0') > min_int % 10) {
						e=Overflow;
						return 0;
					}
					if ((argv[i] - '0') == min_int % 10) {
						i++;
						return min_int;
					}
				}
			}
		}
		ans = ans * 10 + (argv[i++] - '0');
	}
	return ans * znak;
}
state op(int& i, int& sum, int& proizv, const char* argv,error &e) {
	if (e!=Fine) return Fail;
	while (argv[i] == ' ') i++;
	if (argv[i] == '\0') return Suc;
	int plus = (argv[i] == '+'), minus = (argv[i] == '-'), mul = (argv[i] == '*'), del = (argv[i] == '/');
	if ((plus + minus + mul + del) == 0){
		e=Bad_input;
	       	return Fail;
	}
	i++;
	int tmp = to_int(argv, i,e);
	sum = sum + (plus + minus) * proizv;
	if (del) {
		if (tmp) proizv = proizv / tmp;
		else{
			e=Division_by_zero;
		       	return Fail;
		}
	}
	else proizv = plus * tmp - minus * tmp + mul * proizv * tmp;
	return KeepGoing;
}
void err(error e){
	switch (e){
	case Division_by_zero:
		cout<<"Division by zero";
		return;
	case Bad_input:
		cout<<"Bad input";
		return;
	case Overflow:
		cout<<"Overflow";
	}
}

int f(const char* s) {
	error e=Fine;
	int sum = 0,i=0, proizv = to_int(s, i,e);

	state st = KeepGoing;
	while (1) {
		switch (st)
		{
		case Fail:
			err(e);
			return -1;
		case Suc:
			cout << sum + proizv;
			return 0;
		case KeepGoing:
			st = op(i, sum, proizv, s,e);
		}
	}
}

int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "Wrong number of arguments";
		return -1;
	}
	int tmp=max_int;
	while(tmp!=0){// Скольки значное max_int(а также min_int) число
		int_deg++;
		tmp/=10;
	}
	return f(argv[1]);
}
